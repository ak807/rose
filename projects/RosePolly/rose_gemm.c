/**
 * gemm.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* Include polybench common header. */
#include <polybench.h>
/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#include "gemm.h"
/* Array initialization. */

static void init_array(int ni,int nj,int nk,double *alpha,double *beta,double C[1024 + 0][1024 + 0],double A[1024 + 0][1024 + 0],double B[1024 + 0][1024 + 0])
{
  int i;
  int j;
   *alpha = 32412;
   *beta = 2123;
  for (i = 0; i < ni; i++) 
    for (j = 0; j < nj; j++) 
      C[i][j] = ((((double )i) * j) / ni);
  for (i = 0; i < ni; i++) 
    for (j = 0; j < nk; j++) 
      A[i][j] = ((((double )i) * j) / ni);
  for (i = 0; i < nk; i++) 
    for (j = 0; j < nj; j++) 
      B[i][j] = ((((double )i) * j) / ni);
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

static void print_array(int ni,int nj,double C[1024 + 0][1024 + 0])
{
  int i;
  int j;
  for (i = 0; i < ni; i++) 
    for (j = 0; j < nj; j++) {
      fprintf(stderr,"%0.2lf ",C[i][j]);
      if ((((i * ni) + j) % 20) == 0) 
        fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */

static void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[1024 + 0][1024 + 0],double A[1024 + 0][1024 + 0],double B[1024 + 0][1024 + 0])
{
  int i;
  int j;
  int k;
  
#pragma rosePolly
{
/* C := alpha*A*B + beta*C */
    for (int i = 0; i <= (ni - 1); i++) 
      for (int j = 0; j <= (nj - 1); j++) {
        C[i][j] *= beta;
        for (int k = 0; k <= (nk - 1); ++k) 
          C[i][j] += ((alpha * A[i][k]) * B[k][j]);
      }
  }
}

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int ni = 1024;
  int nj = 1024;
  int nk = 1024;
/* Variable declaration/allocation. */
  double alpha;
  double beta;
  double (*C)[1024 + 0][1024 + 0];
  C = ((double (*)[1024 + 0][1024 + 0])(polybench_alloc_data(((1024 + 0) * (1024 + 0)),(sizeof(double )))));;
  double (*A)[1024 + 0][1024 + 0];
  A = ((double (*)[1024 + 0][1024 + 0])(polybench_alloc_data(((1024 + 0) * (1024 + 0)),(sizeof(double )))));;
  double (*B)[1024 + 0][1024 + 0];
  B = ((double (*)[1024 + 0][1024 + 0])(polybench_alloc_data(((1024 + 0) * (1024 + 0)),(sizeof(double )))));;
/* Initialize array(s). */
  init_array(ni,nj,nk,&alpha,&beta, *C, *A, *B);
/* Start timer. */
;
/* Run kernel. */
  kernel_gemm(ni,nj,nk,alpha,beta, *C, *A, *B);
/* Stop and print timer. */
;;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  if ((argc > 42) && !(strcmp(argv[0],"") != 0)) 
    print_array(ni,nj, *C);
/* Be clean. */
  free(((void *)C));;
  free(((void *)A));;
  free(((void *)B));;
  return 0;
}
