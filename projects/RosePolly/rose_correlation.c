/**
 * correlation.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "correlation.h"
/* Array initialization. */

static void init_array(int m,int n,double *float_n,double data[1000 + 0][1000 + 0])
{
  int i;
  int j;
   *float_n = 1.2;
  for (i = 0; i < m; i++) 
    for (j = 0; j < n; j++) 
      data[i][j] = ((((double )i) * j) / 1000);
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

static void print_array(int m,double symmat[1000 + 0][1000 + 0])
{
  int i;
  int j;
  for (i = 0; i < m; i++) 
    for (j = 0; j < m; j++) {
      fprintf(stderr,"%0.2lf ",symmat[i][j]);
      if ((((i * m) + j) % 20) == 0) 
        fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */

static void kernel_correlation(int m,int n,double float_n,double data[1000 + 0][1000 + 0],double symmat[1000 + 0][1000 + 0],double mean[1000 + 0],double stddev[1000 + 0])
{
// int i, j, j1, j2;
  double eps = 0.1f;
#define sqrt_of_array_cell(x,j) sqrt(x[j])
  
#pragma rosePolly
{
/* Determine mean of column vectors of input data matrix */
    for (int j = 0; j <= (m - 1); j++) {
      mean[j] = 0.0;
      for (int i = 0; i <= (n - 1); i++) 
        mean[j] += data[i][j];
      mean[j] /= float_n;
    }
/* Determine standard deviations of column vectors of data matrix. */
    for (int j = 0; j <= (m - 1); j++) {
      stddev[j] = 0.0;
      for (int i = 0; i <= (n - 1); i++) 
        stddev[j] += ((data[i][j] - mean[j]) * (data[i][j] - mean[j]));
      stddev[j] /= float_n;
      stddev[j] = sqrt(stddev[j]);
/* The following in an inelegant but usual way to handle
	 near-zero std. dev. values, which below would cause a zero-
	 divide. */
      if (stddev[j] <= eps) 
        stddev[j] = 1.0;
// stddev[j] = stddev[j] <= eps ? 1.0 : stddev[j];
    }
/* Center and reduce the column vectors. */
    for (int i = 0; i <= (n - 1); i++) 
      for (int j = 0; j <= (m - 1); j++) {
        data[i][j] -= mean[j];
        data[i][j] /= (sqrt(float_n) * stddev[j]);
      }
/* Calculate the m * m correlation matrix. */
    for (int j1 = 0; j1 <= ((m - 1) - 1); j1++) {
      symmat[j1][j1] = 1.0;
      for (int j2 = (j1 + 1); j2 <= (m - 1); j2++) {
        symmat[j1][j2] = 0.0;
        for (int i = 0; i <= (n - 1); i++) 
          symmat[j1][j2] += (data[i][j1] * data[i][j2]);
        symmat[j2][j1] = symmat[j1][j2];
      }
    }
    symmat[m - 1][m - 1] = 1.0;
  }
}

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = 1000;
  int m = 1000;
/* Variable declaration/allocation. */
  double float_n;
  double (*data)[1000 + 0][1000 + 0];
  data = ((double (*)[1000 + 0][1000 + 0])(polybench_alloc_data(((1000 + 0) * (1000 + 0)),(sizeof(double )))));;
  double (*symmat)[1000 + 0][1000 + 0];
  symmat = ((double (*)[1000 + 0][1000 + 0])(polybench_alloc_data(((1000 + 0) * (1000 + 0)),(sizeof(double )))));;
  double (*mean)[1000 + 0];
  mean = ((double (*)[1000 + 0])(polybench_alloc_data((1000 + 0),(sizeof(double )))));;
  double (*stddev)[1000 + 0];
  stddev = ((double (*)[1000 + 0])(polybench_alloc_data((1000 + 0),(sizeof(double )))));;
/* Initialize array(s). */
  init_array(m,n,&float_n, *data);
/* Start timer. */
;
/* Run kernel. */
  kernel_correlation(m,n,float_n, *data, *symmat, *mean, *stddev);
/* Stop and print timer. */
;;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  if ((argc > 42) && !(strcmp(argv[0],"") != 0)) 
    print_array(m, *symmat);
/* Be clean. */
  free(((void *)data));;
  free(((void *)symmat));;
  free(((void *)mean));;
  free(((void *)stddev));;
  return 0;
}
