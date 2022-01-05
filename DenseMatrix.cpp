#include "Util.h"
#include "DenseMatrix.h"

extern "C"
{
  FORTRAN_RET_T
  FORTRAN(dgetrs, DGETRS) (const int& trans,
                           const int& n,
                           const int& nb,
                           double* a,
                           const int& lda,
                           int* ipiv,
                           double* b,
                           const int& ldb,
                           int &info);
}

extern "C" {
  FORTRAN_RET_T
  FORTRAN(dgetrf, DGETRF) (const int&, // M
                            const int&, // N
                           double*, // A
                            const int&, // LDA
                            int *, //IPIV
                            int &); //INFO

  FORTRAN_RET_T
  FORTRAN(dgetri, DGETRI) (const int&, // M
                            double*, // A
                            const int&, // LDA
                            int *, //IPIV
                            double *, // WORK
                            const int&, // LWORK
                            int &); //INFO

}

void solveLU(DoubleDenseMatrix &A, DoubleDenseMatrix &B)
{
  int info;
  FORTRAN(dgetrs,DGETRS)('N',A.n,B.n,A.p,A.lda,A.piv,B.p,B.lda,info);
}

void lu(DenseMatrix<double,double> &A, int *ipiv)
{
  int n = A.n;
  int info;
  FORTRAN(dgetrf,DGETRF)(n,n,A.p,A.lda,ipiv,info);
}

template<>
void DoubleDenseMatrix :: LU()
{
  piv = ReferenceCountingPointer<int>(m);
  lu(*this,piv);
}


extern "C"
{
  FORTRAN_RET_T
  FORTRAN(dgemm, DGEMM) (const int& transa,
                         const int& transb,
                         const int& m,
                         const int& n,
                         const int& k,
                         const double &alpha,
                         double* a,
                         const int& lda,
                         double* b,
                         const int& ldb,
                         const double &beta,
                         double* c,
                         const int& ldc);
}

void multiply_A_Bdagger(DenseMatrix<double,double> &A, DenseMatrix<double,double> &B, DenseMatrix<double,double> &C)
{
  int m = A.m;
  int n = B.m;
  int k = A.n;
  C.resize(A.m,B.m);
  FORTRAN(dgemm,DGEMM)('N','C',m,n,k,1.0,A.p,A.lda,B.p,B.lda,0.0,C.p,C.lda);
}

void multiply_Adagger_B(DenseMatrix<double,double> &A, DenseMatrix<double,double> &B, DenseMatrix<double,double> &C)
{
  int m = A.n;
  int n = B.n;
  int k = A.m;
  C.resize(A.n,B.n);
  FORTRAN(dgemm,DGEMM)('C','N',m,n,k,1.0,A.p,A.lda,B.p,B.lda,0.0,C.p,C.lda);
}
