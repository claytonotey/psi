#ifndef PSI_H
#define PSI_H

#include <vector>
#include <deque>
using namespace std;

enum {
  ImageSize = 3000,
  ImageLeft = 785,
  ImageRight = 2215
};

enum {
  MinPeak = 4,
  MaxPeak = 13,
  NumMinima = (MaxPeak-MinPeak),
  NumMaxima = (MaxPeak-MinPeak),
  NumExtrema = NumMinima + NumMaxima
};


class Session;

class Frame {
public:
  float minima[NumMinima];
  float maxima[NumMaxima];
  int condition;
  float time;
  float minFrame;
  double fv0;
  double fv;
  double getVisibility(int fringe, double absmin, int offset);
  Frame(float *extrema, int condition, float time);
};

class Session {
public:
  bool bRobot;
  double time;
  vector<Frame> frames;
  vector<double> conditionTimes;
  Session(bool bRobot, double time, double *conditionTimes, int nTimes);
  double getMin(double absmin);
  void analyzePairs(double lag, double tau, vector<double> &dfvs);
};

class Sessions {
public:
  deque<Session> sessions;
  Sessions(const char *dirname);
  vector< vector< vector<double> > > analyzeFringe(double lag, double tau, double outlier);
  void getTrend();
  void getVisibilities(int fringe, double absmin, int bRandom, int offset);
  void removeOutliers(vector< vector<double> > &dfvs, double outlierRatio);
};


#endif
