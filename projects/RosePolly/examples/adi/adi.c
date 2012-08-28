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
    int i, j, k, l, m, n, t;

    int i1, i2;

    double t_start, t_end;

	int TT = bar();
	int NN = bar();

    init_array();

#ifdef PERFCTR
    PERF_INIT; 
#endif

    IF_TIME(t_start = rtclock());

#pragma rosePolly
{
    for (int t = 0; t < TT; t++) {

        for (int i1=0; i1<NN; i1++) {
            for (int i2 = 1; i2 < NN; i2++) {
                X[i1][i2] = X[i1][i2] - X[i1][i2-1] * A[i1][i2] / B[i1][i2-1];
                B[i1][i2] = B[i1][i2] - A[i1][i2] * A[i1][i2] / B[i1][i2-1];
            }
        }

        for (int i1=1; i1<NN; i1++) {
            for (int i2 = 0; i2 < NN; i2++) {
                X[i1][i2] = X[i1][i2] - X[i1-1][i2] * A[i1][i2] / B[i1-1][i2];
                B[i1][i2] = B[i1][i2] - A[i1][i2] * A[i1][i2] / B[i1-1][i2];
            }
        }
    }
}

    IF_TIME(t_end = rtclock());
    IF_TIME(fprintf(stderr, "%0.6lfs\n", t_end - t_start));

#ifdef PERFCTR
    PERF_EXIT; 
#endif

    if (fopen(".test", "r")) {
        print_array();
    }
    return 0;
}
