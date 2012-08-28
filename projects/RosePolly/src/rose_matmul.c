#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "timer.h"
#define alpha 1
#define beta 1
int bar2();

int main()
{
  int i;
  int j;
  int k;
  double cpu_start;
  double cpu_end;
  double gpu_start;
  double gpu_end;
  int N = bar2();
  int **A;
  int **B;
  int **C;
  int **cpu_C;
  A = ((int **)(malloc((N * sizeof(int *)))));
  B = ((int **)(malloc((N * sizeof(int *)))));
  C = ((int **)(malloc((N * sizeof(int *)))));
  cpu_C = ((int **)(malloc((N * sizeof(int *)))));
  for (i = 0; i < N; i++) {
    A[i] = ((int *)(malloc((N * sizeof(int )))));
    B[i] = ((int *)(malloc((N * sizeof(int )))));
    C[i] = ((int *)(malloc((N * sizeof(int )))));
    cpu_C[i] = ((int *)(malloc((N * sizeof(int )))));
  }
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = (i + j);
      B[i][j] = (i * j);
      C[i][j] = 0;
    }
  }
  cpu_start = rtclock();
  for (i = 0; i < N; i += 1) 
    for (j = 0; j < N; j += 1) 
      for (k = 0; k < N; k += 1) 
        cpu_C[i][j] = ((1 * cpu_C[i][j]) + ((1 * A[i][k]) * B[k][j]));
  cpu_end = rtclock();
  printf("CPU time -> %0.6lfs\n",(cpu_end - cpu_start));
  gpu_start = rtclock();
  
#pragma rosePolly
{
    for (int i = 0; i <= (N - 1); i++) 
      for (int j = 0; j <= (N - 1); j++) 
        for (int k = 0; k <= (N - 1); k++) 
          C[i][j] = ((1 * C[i][j]) + ((1 * A[i][k]) * B[k][j]));
  }
  gpu_end = rtclock();
  printf("GPU time -> %0.6lfs\n",(gpu_end - gpu_start));
  for (i = 0; i < N; i++) 
    for (j = 0; j < N; j++) 
      (cpu_C[i][j] == C[i][j])?((void )0) : __assert_fail("cpu_C[i][j]==C[i][j]","matmul.c",67,"int main()");
  for (i = 0; i < N; i++) {
    free(A[i]);
    free(B[i]);
    free(C[i]);
    free(cpu_C[i]);
  }
  free(A);
  free(B);
  free(C);
  free(cpu_C);
  return 0;
}
