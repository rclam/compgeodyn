#include <stdio.h>
#include <math.h>
#include <sys/time.h>

/*!!!! Include the proper OpenMP header file here */

int main()
{
  double deltax, area, x, pi, pi_exact, dt;
  int its, mts, itrial;
  long i, n;

  struct timeval tstart, tstop;

  /* Get the number of threads using the _OPENMP #define */
#ifdef _OPENMP
  /* get mps from the correct function call */
  mts = ...
  printf("Method 1 :: Number of Threads is %d\n", mts);
#endif

  /* Print thread numbers */
#pragma omp parallel private(its)
  {
/*!!!! Print the thread numbers, use the omp_get_thread_num function */
    its = ...
    printf("This is Thread %d\n", its); 
  }

  pi_exact = 2. * acos(0.);

  for (itrial=1; itrial<=4; itrial++)
    {
      /* Number of iterations, 10^(itrial+5) */
      n = powl(10, itrial+5);

      /* Integration grid spacing */
      deltax = 2. / (double) n;

      /* Initialize the area for each trial */
      area = 0.;
      
      /* Start the timer */
      gettimeofday (&tstart, NULL);

/*!!!! Finish the parallel do, use a reduction */
#pragma omp parallel for reduction(...) default(none) private(...) shared (...)
      for (i=1; i<=n; i++)
	{
	  x = -1. + i*deltax;
	  area += sqrt(1.-x*x) * deltax;
	}

      /* We integrated from -1 to 1, so multiply the result by 2 to get the full circle */
      pi = 2. * area;

      /* Stop the timer */
      gettimeofday (&tstop, NULL);

      /* Compute the elapsed time */
      dt =
	(double)(tstop.tv_sec  - tstart.tv_sec) +
	(double)(tstop.tv_usec - tstart.tv_usec)*1.e-6;

      /* Print out the integration and timing results */
      printf("Number of intervals : %12ld, pi = %22.21e, delta = %g, time = %fs\n", n, pi, pi-pi_exact, dt);
    }

  return 0;
}
