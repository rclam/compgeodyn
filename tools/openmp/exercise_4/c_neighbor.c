#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "omp.h"

/***
 * This example implements a pseudo finite-difference stencil.
 * The initial data is stored in the array 'a' and the result
 * of the stencil is stored in b.
 *
 * b[i][j] is created from a linear combination
 * of values
 *                     North (1 row above)
 * West (1 col left)                          East (1 col right)
 *                     South (1 row below)
 *
 * and, similarly
 *
 * NorthWest NorthEast
 * SouthWest SouthEast
 *
 * We use the following #define's to make the action of the stencil
 * more clear below.
 */
#define North i-1][j
#define South i+1][j
#define West  i][j+1
#define East  i][j-1
#define NorthWest i-1][j+1
#define NorthEast i-1][j-1
#define SouthWest i+1][j+1
#define SouthEast i+1][j-1
	      

int main()
{
  /* matrix size and operation complexity parameters */
  const int n=160, m=10000;

  double a[n][n], b[n][n];
  double dt, xk, xk2;
  int mts, i, j, k, j_update;
  
  struct timeval tstart, tstop;

  /* Get the number of threads using the _OPENMP #define */
#ifdef _OPENMP
  mts = omp_get_max_threads();
  printf("Method 1 :: Number of Threads is %d\n", mts);
#endif

  // Zero out stack values
  memset(a, 0, sizeof(a));
  memset(b, 0, sizeof(a));

  /* Fill in a (a is symmetric) */

  /* Lower half */
  for (i=0; i<n; i++)
    for (j=0; j<=i; j++)
      for (k=1; k<=m; k++)
	a[i][j] += (double) ((i+1)*(j+1)) / (double) (i+1 + j+1 + k);

  /* Copy lower triangle of a into upper */
  for (i=0; i<n; i++)
    for (j=i+1; j<n; j++)
      a[i][j] = a[j][i];

  /* Start the timer */
  gettimeofday (&tstart, NULL);

  /***
   * Calculate b
   */
  /*!!!! Start your parallel region here */
#pragma omp ... default(none) private(i, j, k, xk, xk2) shared(a, b, j_update)
  {
/* !!!! Initialize j_update with one OpenMP thread */
#pragma omp ...
    { j_update = 0; }

/* !!!! Try different scheduling options: static, dynamic, guided */
#pragma omp for schedule(...)
    for (i=1; i<=n-2; i++)
      for (j=1; j<=i; j++)
	{
/* !!!! Update j_update with one OpenMP thread */
#pragma omp ...
	  { j_update += 1; }

	  /* Loop over k to compute the entry in b */
	  for (k=1; k<=m; k++)
	    {
	      xk = (double) k;
	      xk2 = xk * xk;

	      b[i][j] +=
		(a[North]     + a[South]     + a[West]      + a[East]     ) / xk +
		(a[NorthWest] + a[NorthEast] + a[SouthWest] + a[SouthEast]) / xk2
		;
	    }
	} /* end j loop */
  } /* end omp parallel section */

  /* Stop the timer and compute the elapsed time. */
  gettimeofday (&tstop, NULL);
  
  /* Compute the elapsed time */
  dt =
    (double)(tstop.tv_sec  - tstart.tv_sec) +
    (double)(tstop.tv_usec - tstart.tv_usec)*1.e-6;

  /* Print the results */
  printf("b(1,1), b(n-2,n-2) = %6.5e, %6.5e, ", b[1][1], b[n-2][n-2]);
  printf("Number of j updates = %d, ", j_update);
  printf("time = %4.3es\n", dt);
  
  return 0;
}
