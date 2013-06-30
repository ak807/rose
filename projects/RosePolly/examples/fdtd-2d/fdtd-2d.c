#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <assert.h>

#ifdef PERFCTR
#include <papi.h>
#include "papi_defs.h"
#endif

extern int foo();
extern int bar();
extern int car();

/* #define tmax 128
#define nx 4000
#define ny 4000 */

int tmax,nx,ny;

/* #pragma declarations
double ex[nx][ny+1];
double ey[nx+1][ny];
double hz[nx][ny];
#pragma enddeclarations */

// #include "util.h"

double t_start, t_end;

int main()
{
	int m, n;

	tmax = foo();
	nx = bar();
	ny = car();

	double ex[nx][ny+1];
double ey[nx+1][ny];
double hz[nx][ny];

	init_array() ;

#ifdef PERFCTR
    PERF_INIT;
#endif

	IF_TIME(t_start = rtclock());

#pragma rosePolly
{
    for(int t=0; t<tmax; t++)  {
        for (int j=0; j<ny; j++)
            ey[0][j] = t;
        for (int i=1; i<nx; i++)
            for (int j=0; j<ny; j++)
                ey[i][j] = ey[i][j] - 0.5*(hz[i][j]-hz[i-1][j]);
        for (int i=0; i<nx; i++)
            for (int j=1; j<ny; j++)
                ex[i][j] = ex[i][j] - 0.5*(hz[i][j]-hz[i][j-1]);
        for (int i=0; i<nx; i++)
            for (int j=0; j<ny; j++)
                hz[i][j]=hz[i][j]-0.7*(ex[i][j+1]-ex[i][j]+ey[i+1][j]-ey[i][j]);
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
