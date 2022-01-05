#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include "ReferenceCountingPointer.h"
#include <iostream>
#include <fstream>
#include "Array.h"
#include <vector>
using namespace std;

template<class R, class T>
class DenseMatrix {
 public:

 DenseMatrix(int m_, int n_) : m(m_), n(n_), lda(m_), p(m_*n_), piv() {
  }

  int getNumRows() const { return m; }
  int getNumCols() const { return n; }

  void zero() 
  {
    if(p) {
      for(int j=0; j<n; j++) {
        memset(p+j*lda,0,m*sizeof(T));
      }
    }
  }

  void resize(int is, int js, int m, int n) 
  {
    if(p) {
      p = ReferenceCountingPointer<T>(p,is+js*lda);
    } else {
      p = ReferenceCountingPointer<T>(m*n);
      lda = m;
    }
    this->m = m;
    this->n = n;
  }

  void resize(int m, int n) 
  {
    resize(0,0,m,n);
  }

  inline T& operator()(int i, int j)
  {
    return p[i + lda * j];
  }

  inline T& operator()(int i, int j) const
  {
    return p[i + lda * j];
  }

  void LU();

 public:
  int m;
  int n;
  int lda;
  ReferenceCountingPointer<T> p;
  ReferenceCountingPointer<int> piv;
};

template<class R, class T1, class T2>
void solve(DenseMatrix<R,T1> &A, DenseMatrix<R,T2> &B)
{
  int m = B.m;

  if(A.m != A.n || A.n != m)
    abort();

  A.LU();
  solveLU(A,B);
}

typedef DenseMatrix<double,double> DoubleDenseMatrix;

void solveLU(DoubleDenseMatrix &A, DoubleDenseMatrix &B);
void lu(DenseMatrix<double,double> &A, int *ipiv);
void multiply_A_Bdagger(DenseMatrix<double,double> &A, DenseMatrix<double,double> &B, DenseMatrix<double,double> &C);
void multiply_Adagger_B(DenseMatrix<double,double> &A, DenseMatrix<double,double> &B, DenseMatrix<double,double> &C);

#endif
