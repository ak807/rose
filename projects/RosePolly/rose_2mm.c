/**
 * 2mm.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "2mm.h"
/* Array initialization. */

static void init_array(int ni,int nj,int nk,int nl,double *alpha,double *beta,double A[1024 + 0][1024 + 0],double B[1024 + 0][1024 + 0],double C[1024 + 0][1024 + 0],double D[1024 + 0][1024 + 0])
{
  int i;
  int j;
   *alpha = 32412;
   *beta = 2123;
  for (i = 0; i < ni; i++) 
    for (j = 0; j < nk; j++) 
      A[i][j] = ((((double )i) * j) / ni);
  for (i = 0; i < nk; i++) 
    for (j = 0; j < nj; j++) 
      B[i][j] = ((((double )i) * (j + 1)) / nj);
  for (i = 0; i < nl; i++) 
    for (j = 0; j < nj; j++) 
      C[i][j] = ((((double )i) * (j + 3)) / nl);
  for (i = 0; i < ni; i++) 
    for (j = 0; j < nl; j++) 
      D[i][j] = ((((double )i) * (j + 2)) / nk);
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

static void print_array(int ni,int nl,double D[1024 + 0][1024 + 0])
{
  int i;
  int j;
  for (i = 0; i < ni; i++) 
    for (j = 0; j < nl; j++) {
      fprintf(stderr,"%0.2lf ",D[i][j]);
      if ((((i * ni) + j) % 20) == 0) 
        fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */

static void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double tmp[1024 + 0][1024 + 0],double A[1024 + 0][1024 + 0],double B[1024 + 0][1024 + 0],double C[1024 + 0][1024 + 0],double D[1024 + 0][1024 + 0])
{
  int i;
  int j;
  int k;
  
#pragma rosePolly
{
/* D := alpha*A*B*C + beta*D */
    for (int i = 0; i <= (ni - 1); i++) 
      for (int j = 0; j <= (nj - 1); j++) {
        tmp[i][j] = 0;
        for (int k = 0; k <= (nk - 1); ++k) 
          tmp[i][j] += ((alpha * A[i][k]) * B[k][j]);
      }
    for (int i = 0; i <= (ni - 1); i++) 
      for (int j = 0; j <= (nl - 1); j++) {
        D[i][j] *= beta;
        for (int k = 0; k <= (nj - 1); ++k) 
          D[i][j] += (tmp[i][k] * C[k][j]);
      }
  }
}

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int ni = 1024;
  int nj = 1024;
  int nk = 1024;
  int nl = 1024;
/* Variable declaration/allocation. */
  double alpha;
  double beta;
  double (*tmp)[1024 + 0][1024 + 0];
  tmp = ((double (*)[1024 + 0][1024 + 0])(polybench_alloc_data(((1024 + 0) * (1024 + 0)),(sizeof(double )))));;
  double (*A)[1024 + 0][1024 + 0];
  A = ((double (*)[1024 + 0][1024 + 0])(polybench_alloc_data(((1024 + 0) * (1024 + 0)),(sizeof(double )))));;
  double (*B)[1024 + 0][1024 + 0];
  B = ((double (*)[1024 + 0][1024 + 0])(polybench_alloc_data(((1024 + 0) * (1024 + 0)),(sizeof(double )))));;
  double (*C)[1024 + 0][1024 + 0];
  C = ((double (*)[1024 + 0][1024 + 0])(polybench_alloc_data(((1024 + 0) * (1024 + 0)),(sizeof(double )))));;
  double (*D)[1024 + 0][1024 + 0];
  D = ((double (*)[1024 + 0][1024 + 0])(polybench_alloc_data(((1024 + 0) * (1024 + 0)),(sizeof(double )))));;
/* Initialize array(s). */
  init_array(ni,nj,nk,nl,&alpha,&beta, *A, *B, *C, *D);
/* Start timer. */
;
/* Run kernel. */
  kernel_2mm(ni,nj,nk,nl,alpha,beta, *tmp, *A, *B, *C, *D);
/* Stop and print timer. */
;;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  if ((argc > 42) && !(strcmp(argv[0],"") != 0)) 
    print_array(ni,nl, *D);
/* Be clean. */
  free(((void *)tmp));;
  free(((void *)A));;
  free(((void *)B));;
  free(((void *)C));;
  free(((void *)D));;
  return 0;
}
