#include "Util.h"
#include <cassert>

#define MAXIT 100

int zbrac(const std::function<void(double, double *, double *)> &fdf, double *x1, double *x2)
{
  int j;
  double f1,f2;
  double meh;
  fdf(*x1, &f1, &meh);
  fdf(*x2, &f2, &meh);
  for(j=1;j<=8;j++) {
    if(f1*f2 < 0.0) return 1; 
    if(fabs(f1) < fabs(f2)) {
      *x1 += 1.6*(*x1-*x2);
      fdf(*x1, &f1, &meh);
    } else {
      *x2 += 1.6*(*x2-*x1);
      fdf(*x2, &f2, &meh);
    }
  }
  return 0; 
}

double rtsafe(const std::function<void(double, double *, double *)> &fdf, double x1, double x2, double xacc)
{
  double df,dx,dxold,f,fh,fl;
  double temp,xh,xl,rts;
  fdf(x1,&fl,&df);
  fdf(x2,&fh,&df);
  //assert(!((fl > 0.0 && fh > 0.0) || (fl < 0.0 && fh < 0.0)));
  if(((fl > 0.0 && fh > 0.0) || (fl < 0.0 && fh < 0.0))) {
    printf("%g %g %g %g\n",fl,fh);
    abort();
  }

  if (fh == 0.0) return x2;
  if (fl < 0.0) {
    xl=x1;
    xh=x2;
  } else {
    xh=x1;
    xl=x2; 
  }
  rts=0.5*(x1+x2); dxold=fabs(x2-x1); dx=dxold; fdf(rts,&f,&df);
  for(int j=1;j<=MAXIT;j++) {
    if ((((rts-xh)*df-f)*((rts-xl)*df-f) > 0.0)
        || (fabs(2.0*f) > fabs(dxold*df))) { 
      dx=0.5*(xh-xl);
      rts=xl+dx;
      if (xl == rts) return rts; 
    } else {
      dxold=dx;
      dx=f/df;
      temp=rts;
      rts -= dx;
      if (temp == rts) return rts;
    }
    if (fabs(dx) < xacc) return rts; fdf(rts,&f,&df);
    if (f < 0.0) 
      xl=rts;
    else 
      xh=rts;
  }
  assert(false);
}
