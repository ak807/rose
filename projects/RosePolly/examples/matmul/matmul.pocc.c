#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define M 1024
#define N 1024
#define K 1024
#define alpha 1
#define beta 1

#pragma declarations
double A[M][K];
double B[K][N];
double C[M][N];
#pragma enddeclarations

#ifdef PERFCTR
#include "papiStdEventDefs.h"
#include <papi.h>
#include "papi_defs.h"
#endif

#include "util.h"

double t_start, t_end;

int main()
{
    int i, j, k;

    init_array();

#ifdef PERFCTR
    PERF_INIT; 
#endif

    IF_TIME(t_start = rtclock());

#ifdef ceild
# undef ceild
#endif
#ifdef floord
# undef floord
#endif
#ifdef max
# undef max
#endif
#ifdef min
# undef min
#endif
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))

  register int lbv, ubv, lb, ub, lb1, ub1, lb2, ub2;
  register int c1t1, c3t1, c5t1, c1, c3, c5;

#pragma scop
if ((((K >= 1) && (M >= 1)) && (N >= 1))) {
  lb1 = round((-1 + (1 / T1c1)));
  ub1 = round(((M * (1 / T1c1)) + ((1 / T1c1) * -1)));
#pragma omp parallel for private(c3t1, c5t1, c1, c3, c5) firstprivate(lb1, ub1)
    for (c1t1 = lb1; c1t1 <= ub1; ++(c1t1)) {
        for (c3t1 = round((-1 + (1 / T1c3))); c3t1 <= round(((N * (1 / T1c3)) + ((1 / T1c3) * -1))); ++(c3t1)) {
            for (c5t1 = round((-1 + (1 / T1c5))); c5t1 <= round(((K * (1 / T1c5)) + ((1 / T1c5) * -1))); ++(c5t1)) {
                for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (M + -1)); c1++) {
                    for (c3 = max((c3t1 * T1c3), 0); c3 <= min(((c3t1 * T1c3) + (T1c3 + -1)), (N + -1)); c3++) {
                        for (c5 = max((c5t1 * T1c5), 0); c5 <= min(((c5t1 * T1c5) + (T1c5 + -1)), (K + -1)); c5++) {
              C[c1][c3]=beta*C[c1][c3]+alpha*A[c1][c5]*B[c5][c3];
            }
          }
        }
      }
    }
  }
}
#pragma endscop

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
