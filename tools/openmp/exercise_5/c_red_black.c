#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "omp.h"

int main()
{
  const int n = (int)(1.e8);
  double *a;
  double dt, error;
  int mts;
  int i, niter;

  struct timeval tstart, tstop;

  /* Get the number of threads using the _OPENMP #define */
#ifdef _OPENMP
  mts = omp_get_max_threads();
  printf("Method 1 :: Number of Threads is %d\n", mts);
#endif

  /***
   * Allocate space for the calculation.  We make
   * this on the heap since the test array size is
   * quite large.
   */
  a = (double*)calloc(n, sizeof(double));

  /***
   * Be sure that allocation succeeded.
   */
  if (!a)
    {
      printf("Error while allocating memory, quitting!\n");
      exit(1);
    }

  /* Preset data 0,1,0,1,... */
  for (i=0; i<n; i+=2)
    {
      a[i]   = 0.;
      a[i+1] = 1.;
    }

  /* Start the timer */
  gettimeofday (&tstart, NULL);

  niter = 0;

  do
    {
      niter++;

      /* Update second, fourth, sixth, ... entries */
/* !!!! Parallelize this loop */
      for (i=1; i<n; i+=2)
	a[i] = 0.5 * (a[i] + a[i-1]);

      /* Update first, third, fifth, ... entries */
/* !!!! Parallelize this loop */
      for (i=0; i<n; i+=2)
	a[i] = 0.5 * (a[i] + a[i-1]);

      /* Calculate error */
      error = 0.;
/* !!!! Parallelize this loop, use a reduction */
      for (i=0; i<n-1; i++)
	error += fabs(a[i]-a[i+1]);
      
      /* Print loop information */
      printf("Iteration : %d, error = %3.2e\n", niter, error);
      
    } while (error > 1.);

  /* Stop the timer and compute the elapsed time. */
  gettimeofday (&tstop, NULL);

  /* Compute the elapsed time */
  dt =
    (double)(tstop.tv_sec  - tstart.tv_sec) +
    (double)(tstop.tv_usec - tstart.tv_usec)*1.e-6;

  /***
   * Print the final result and timings.
   */
  printf("Number of iterations : %d, ", niter);
  printf("error = %6.5e, ", error);
  printf("time = %6.5es\n", dt);

  /* Release allocated memory. */
  free(a);
  
  return 0;
}
