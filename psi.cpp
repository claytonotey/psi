#include <iostream>
#include <fstream>
#include <matio.h>
#include <cstdint>
#include <dirent.h>
#include <vector>
#include <string.h>
#include "coroutine.h"
#include <cassert>
#include "DenseMatrix.h"
#include "Util.h"
#include "psi.h"

using namespace std;

generator<int16_t*> readBin(string fn)
{
  int16_t pixels[ImageSize];
  ifstream fs(fn, ios::binary);
  while( fs.read((char*)pixels, sizeof(pixels)) ) {
    assert(fs.gcount()==sizeof(pixels));
    co_yield pixels;
  }
}

class PolySmooth {
public:
  vector<double> C;
  int n;

  PolySmooth(int n, int K) : n(n),  C(n) {
    assert(n%2==1);
    initReferenceCountingPointerLock();
    DoubleDenseMatrix X(n, K);
    DoubleDenseMatrix XtX(K, K);
    DoubleDenseMatrix Xt(K, n);
    int n2 = n/2;
    for(int i=-n2; i<=n2; i++) {
      double x = 1.0;
      for(int j=0; j<K; j++) {
        X(i+n2,j) = x;
        Xt(j,i+n2) = x;
        x *= i;
      }
    }
    multiply_Adagger_B(X,X,XtX);
    solve(XtX,Xt);
    for(int i=0; i<n; i++) {
      C[i] = Xt(0,i);
    }
  }
  
  double smooth(int16_t *x) {
    double y = 0;
    int n2 = n/2;
    for(int i=0; i<n; i++) {
      y += C[i] * x[i-n2];
    }
    return y;
  }
};

static const int SmoothSpan = 31;
static PolySmooth smooth(SmoothSpan,3);

double extremum(int i0, int i2, int16_t *pixels, bool bMin)
{
  double ext = smooth.smooth(pixels+i0);
  for(int i=i0+1; i<i2; i++) {
    double y = smooth.smooth(pixels+i);
    if(bMin) {
      ext = min(y, ext);
    } else {
      ext = max(y, ext);
    }
  }
  //printf("%g %g\n", ext, pixels[i0]);
  return ext;
}

class Frame2 {
public:
  vector<float> maxima;
  vector<float> minima;
  float minFrame;

  const double firstPeak = 800.0;
  const double peakSep = 73.35;
  const double peakWidth = 10.0;

  Frame2(int16_t *pixels) {
    
    minFrame = 1e9;
    for(int i=SmoothSpan/2; i<750; i++) {
      float y = smooth.smooth(pixels+i);
      minFrame = min(minFrame, y);
    }

    for(int i=2250; i<3000-SmoothSpan/2; i++) {
      float y = smooth.smooth(pixels+i);
      minFrame = min(minFrame, y);
    }


    for(int i=MinPeak; i<MaxPeak; i++) {
      double x1 = firstPeak + i*peakSep;
      int x0 = lrintf(x1 - peakWidth);
      int x2 = lrintf(x1 + peakWidth);
      double ymin = extremum(x0, x2, pixels, true);
      minima.push_back(ymin);
      x1 = x1 + 0.5 * peakSep;
      x0 = lrintf(x1 - peakWidth);
      x2 = lrintf(x1 + peakWidth);
      double ymax = extremum(x0, x2, pixels, false);
      maxima.push_back(ymax);

      assert(!isnan(ymin));
      assert(!isnan(ymax));

      assert(!isinf(ymin));
      assert(!isinf(ymax));
      
    }
  }
};

inline ostream &operator<<(ostream &os, const Frame2 &frame)
{
  os.write((char*)&frame.minFrame, sizeof(float));
  os.write((char*)frame.minima.data(), frame.minima.size()*sizeof(float));;
  os.write((char*)frame.maxima.data(), frame.maxima.size()*sizeof(float));;
  return os;
}

int main(int argc, char **argv)
{
  initReferenceCountingPointerLock();

  const char *dir = argv[1];
  string dirname(dir);
  DIR *dirp = opendir(dir);
  dirent *dp;
  int num = 0;
  while((dp = readdir(dirp)) != NULL) {
    if(dp->d_namlen > 3 && !strcmp(dp->d_name+dp->d_namlen-3, "bin")) {
      string filename(dp->d_name);
      //cout << filename << "\n";
      auto reader = readBin(dirname + "/" + filename);
      string extname = dirname + "/" + filename.replace(dp->d_namlen-3,3,"ext");
      ofstream fs(extname, ios::binary);
      int k = 0;
      while(reader.move_next()) {
        //printf("%d\n",k);
        Frame2 frame(reader.current_value());
        fs << frame;
        k++;
      }
      fs.close();
      num++;
      printf("\r%d",num);
      fflush(stdout);
    }
  }
  closedir(dirp);
}
