#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <omp.h>
#ifdef PERFCTR
#include <papi.h>
#include "papi_defs.h"
#endif
#include "decls.h"
#include "util.h"
int bar();

int main()
{
  int i;
  int j;
  int k;
  int l;
  int m;
  int n;
  int t;
  int i1;
  int i2;
  double t_start;
  double t_end;
  int TT = bar();
  int NN = bar();
  init_array();
#ifdef PERFCTR
#endif
  
#pragma rosePolly
;
{
    for (int t = 0; t <= (TT - 1); t++) {
      for (int i1 = 0; i1 <= (NN - 1); i1++) {
        for (int i2 = 1; i2 <= (NN - 1); i2++) {
          X[i1][i2] = (X[i1][i2] - ((X[i1][i2 - 1] * A[i1][i2]) / B[i1][i2 - 1]));
          B[i1][i2] = (B[i1][i2] - ((A[i1][i2] * A[i1][i2]) / B[i1][i2 - 1]));
        }
      }
      for (int i1 = 1; i1 <= (NN - 1); i1++) {
        for (int i2 = 0; i2 <= (NN - 1); i2++) {
          X[i1][i2] = (X[i1][i2] - ((X[i1 - 1][i2] * A[i1][i2]) / B[i1 - 1][i2]));
          B[i1][i2] = (B[i1][i2] - ((A[i1][i2] * A[i1][i2]) / B[i1 - 1][i2]));
        }
      }
    }
  };;
#ifdef PERFCTR
#endif
  if (fopen(".test","r") != 0) {
    print_array();
  }
  return 0;
}
