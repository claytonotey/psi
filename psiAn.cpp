#include <iostream>
#include <fstream>
#include <matio.h>
#include <cstdint>
#include <dirent.h>
#include <vector>
#include <string.h>
#include "coroutine.h"
#include <cassert>
#include <deque>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include "psi.h"

using namespace std;

generator<float*> readExt(string fn)
{
  float data[NumExtrema+1];
  ifstream fs(fn, ios::binary);
  while( fs.read((char*)data, sizeof(data)) ) {
    assert(fs.gcount()==sizeof(data));
    co_yield data;
  }
}

time_t timeFromString(const char *dateTime)
{
  string dateTimeStr(dateTime);
  istringstream ss( dateTimeStr );
  tm dt = {};
  ss >> get_time(&dt, "%d-%b-%Y %H:%M:%S");
  return mktime(&dt);
}


Frame :: Frame(float *data, int condition, float time) :
  condition(condition),
  time(time)
{
  float *extrema = data + 1;
  minFrame = *data;
  memmove(minima, extrema, NumMinima*sizeof(float));
  memmove(maxima, extrema+NumMinima, NumMaxima*sizeof(float));
}

Session :: Session(bool bRobot, double time, double *conditionTimes, int nTimes) :
  bRobot(bRobot), time(time), conditionTimes(conditionTimes, conditionTimes+nTimes) {
}

double Frame :: getVisibility(int fringe, double absmin, int offset)
{
  int k = fringe;
  double minUse;
  if(absmin == -1) {
    minUse = minFrame;
  } else {
    minUse = absmin; 
  }
  if(fringe == -1) {
    double fv = 0;
    for(int k=0; k<NumMinima; k++) {
      fv += (maxima[k+offset] - minima[k]) / (maxima[k+offset] + minima[k] - 2 * minUse);
    }
    return fv / NumMinima;
  } else {
    return (maxima[k+offset] - minima[k]) / (maxima[k+offset] + minima[k] - 2 * minUse);
  }
}

double Session :: getMin(double absmin)
{
  float minSession = 1e9;
  for(auto &&frame : frames) {
    minSession = min(minSession, frame.minFrame);
  }
  if(absmin == -2) {
    absmin = minSession;
  }
  return absmin;
}

double median(vector<double> &v)
{
  assert(v.size());
  sort(v.begin(), v.end());
  int n2 = v.size()>>1;
  if(v.size() & 1) {
    return v[n2];
  } else {
    return 0.5 * (v[n2-1] + v[n2]);
  }
}

void Session :: analyzePairs(double lag, double tau, vector<double> &dfvs)
{
  if(frames.size() < tau) return;
  if(conditionTimes.size() < 3) {
    return;
  }

  vector<double> fvs1;
  vector<double> fvs2;

  /*
  int ilag = lrintf(lag * 4.0 );
  for(int k=0; k<frames.size()-ilag; k++) {
    if(frames[k].condition == 2) {
      fvs2.push_back(frames[k+ilag].fv);
    } else {
      fvs1.push_back(frames[k+ilag].fv);
    }
  }

  if(fvs1.size() && fvs2.size()) {
    double dfv = median(fvs1) - median(fvs2);
    dfvs.push_back(dfv);
  }
  return;
  */

  double condT0 = conditionTimes[0];
  double condT1 = conditionTimes[1];
  double condT2 = conditionTimes[2];
  int condK = 0;

  int pairIndex = 0;
  for(auto &&frame : frames) {
    if(frame.time > condT0 + lag) {
      if(frame.time > condT2 + lag) {
        fvs2.push_back(frame.fv);
        condK += 2;
        if(condK + 2 >= conditionTimes.size()) {
          continue;
        }
        condT0 = conditionTimes[condK];
        condT1 = conditionTimes[condK+1];
        condT2 = conditionTimes[condK+2];
      } else if(frame.time > condT1 + lag) {
        fvs1.push_back(frame.fv);
      } else {
        fvs2.push_back(frame.fv);
      }
    } else {
      // beginnin before lag set in
      //fvs1.push_back(frame.fv);
    }
  }
  if(fvs1.size() && fvs2.size()) {
    double dfv = median(fvs1) - median(fvs2);
    dfvs.push_back(dfv);
  }
}

void Sessions :: removeOutliers(vector< vector<double> > &dfvs, double outlierRatio)
{

}

void Sessions :: getTrend() 
{
  for(auto &&session : sessions) {
      static std::default_random_engine generator;
      static std::normal_distribution<double> distribution(0.0,1.0);    
      double r = .988;

      for(auto &&frame : session.frames) {
        r += .00003 * distribution(generator);
        frame.fv0 = r;
      }
  }
}
        
void Sessions :: getVisibilities(int fringe, double absmin, int bRandom, int offset) 
{
  for(auto &&session : sessions) {
    if(bRandom) {
      static std::default_random_engine generator;
      static std::normal_distribution<double> distribution(0.0,1.0);    
 
      for(auto &&frame : session.frames) {
         frame.fv = frame.fv0 + .0015 * distribution(generator);
      }
    } else {
      float minUse = session.getMin(absmin);
      for(auto &&frame : session.frames) {
        frame.fv = frame.getVisibility(fringe, minUse, offset);
      }
    }
  }
}

vector< vector< vector<double> > > Sessions :: analyzeFringe(double lag, double tau, double outlierRatio) 
{
  vector<vector< vector<double> > > dfvs(2);
          
  for(auto &&session : sessions) {
    vector<double> *sessionDFVS;
    if(session.bRobot) {
      dfvs[0].emplace_back();
      sessionDFVS = &dfvs[0].back();
    } else {
      dfvs[1].emplace_back();
      sessionDFVS = &dfvs[1].back();
    }
    sessionDFVS->reserve(session.frames.size());
    session.analyzePairs(lag, tau, *sessionDFVS);
  }
  removeOutliers(dfvs[0],outlierRatio);
  removeOutliers(dfvs[1],outlierRatio);

  return dfvs;
}

Sessions :: Sessions(const char *dir)
{
  //printf("%s\n",dir);
  DIR *dirp = opendir(dir);
  string dirname(dir);
  dirent *dp;

  int num = 0;
  while((dp = readdir(dirp)) != NULL) {
    string filename(dp->d_name);
    if(dp->d_namlen > 3 && !strcmp(dp->d_name+dp->d_namlen-3, "mat")) {
      string matname(dirname + "/" + filename);
      mat_t *mat = Mat_Open(matname.c_str(), MAT_ACC_RDONLY);
      matvar_t *conditionTimes = Mat_VarRead(mat,"conditionTime");
      matvar_t *conditionValues = Mat_VarRead(mat,"conditionValues");
      matvar_t *timeValues = Mat_VarRead(mat,"timeValues");
      matvar_t *timeOfRecordingVar = Mat_VarRead(mat,"timeOfRecording");
      string extname = dirname + "/" + filename.replace(dp->d_namlen-3,3,"ext");
      auto reader = readExt(extname);
      bool bRobot = filename.find("Robot") != string::npos;

      double timeOfRecording = (double)timeFromString((char*)timeOfRecordingVar->data);
      sessions.emplace_back(bRobot, timeOfRecording, (double*)conditionTimes->data, conditionTimes->dims[1]);
      Session *session = &sessions.back();
      
      int index = 0;
      while(reader.move_next()) {
        int condition = lrintf(((double*)conditionValues->data)[index]);
        float time = ((double*)timeValues->data)[index];
        //time = 0.25 * index;
        session->frames.emplace_back(reader.current_value(), condition, time);
        index++;
      }
      Mat_VarFree(conditionTimes);
      Mat_VarFree(conditionValues);
      Mat_VarFree(timeValues);
      Mat_VarFree(timeOfRecordingVar);
      Mat_Close(mat);
      //cout << extname << " " << timeOfRecording << "\n";
      num++;
      //printf("\r%d",num);
      fflush(stdout);
    }
  }
  closedir(dirp);
}
