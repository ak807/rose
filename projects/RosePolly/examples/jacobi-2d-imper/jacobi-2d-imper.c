#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <assert.h>

/* #define N 2000
#define T 2000 */

extern int foo();
extern int bar();

int N,T;

/* #pragma declarations
double a[N][N];
double b[N][N];
#pragma enddeclarations */

#include "util.h"

int main()
{
    // int t, i, j;
    double t_start, t_end;

	N = foo();
	T = bar();

	double a[N][N];
double b[N][N];

    init_array(a);

    IF_TIME(t_start = rtclock());

#pragma rosePolly
{
    for (int t=0; t<T; t++) {
        for (int i=2; i<N-1; i++) {
            for (int j=2; j<N-1; j++) {
                b[i][j]= 0.2*(a[i][j]+a[i][j-1]+a[i][1+j]+a[1+i][j]+a[i-1][j]);
            }
        }
        for (int i=2; i<N-1; i++) {
            for (int j=2; j<N-1; j++)   {
                a[i][j]=b[i][j];
            }
        }
    }
}

    IF_TIME(t_end = rtclock());
    IF_TIME(fprintf(stderr, "%0.6lfs\n", t_end - t_start));

    if (fopen(".test", "r")) {
        print_array(a);
    }
    return 0;
}
