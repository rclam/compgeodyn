#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "omp.h"

/* Function prototype ... */
void printer_sub();

int main()
{
  int mts, i, its1, its2, its5;
  
  /* Get the number of threads using the _OPENMP #define */
#ifdef _OPENMP
  mts = omp_get_max_threads();
  printf("Method 1 :: Number of Threads is %d\n", mts);
#endif

#pragma omp parallel default(none) private(its1, its2, its5)
  {
    its1 = omp_get_thread_num();
    printf("Print #1, its1 = %d\n", its1);

#pragma omp for private(i)
    for (i=1; i<=5; i++)
      {
	its2 = omp_get_thread_num();
	printf("Print #2, its2 = %d\n", its2);
      }

    printer_sub();

#pragma omp master
    {
      its5 = omp_get_thread_num();
      printf("Print #5, its5 = %d\n", its5);
    } /* end omp master */
    
  } /* end omp parallel */
  
  return 0;
}



void printer_sub()
{
  int i, its3, its4;

#pragma omp for
  for (i=1; i<=3; i++)
    {
      its3 = omp_get_thread_num();
      printf("Print #3, its3 = %d\n", its3);
    }

  for (i=1; i<=3; i++)
    {
      its4 = omp_get_thread_num();
      printf("Print #4, its4 = %d\n", its4);
    }
}
