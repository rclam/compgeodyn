#include <stdio.h>
#include <stdlib.h>

int i, j, indx;
int sflag;
int sum;

void populateArray(int nelem_in_array, int *array);
void sortArray(int nelem_in_array, int *array, int (*fcn)(int sortFlag, int n, int m));
void exchange(int *elem1, int *elem2);
int ascending(int sortFlag, int n, int m);
int descending(int sortFlag, int n, int m);
int sumElements(int nelem_in_array, int *array);
float getAverage(int nelem_in_array, int *array);

int main(void)
{
  const int nelem = 10;

  int *array;
  array = (int *)malloc(nelem*sizeof(int));

/*  Initialize the arrays  */
  for (indx = 0; indx < nelem; indx++)
  {
    array[indx] = 0;
  }

/* Replace initial values of array elements  */
  populateArray(nelem, array);

/* Print the elements of the unsorted array  */
  printf("The sequence of elements in the unsorted array are: [ ");

  for (indx = 0; indx < nelem; indx++)
  { 
    printf("%d ", array[indx]);
  }
  printf("]\n\n");

/* Sort the array of integers  */
  sortArray(nelem, array, ascending);

/* Print the elements of the sorted array  */
  printf("The sequence of elements in the sorted array are: [ ");
  for (indx = 0; indx < nelem; indx++)
  {
    printf("%d ", array[indx]);
  }
  printf("]\n\n");

/*  Compute average value of elements in array  */
  getAverage(nelem, array); 

/* Print sum of elements in array  */
  printf("The sum of the %d elements in the array is: %d\n\n ", nelem, sum);

/*  Print average */
/*  printf("The average value of the array elements is: %f\n\n ", getAverage(nelem, array));  */

  free(array);

  return 0;
}

void populateArray(const int nelem_in_array, int *intArray)
{
  for (j = 0; j < nelem_in_array; j++)
  {
    if ((j % 2) == 0)
    {
      *intArray = 10;
    }
    else
    {
      *intArray = 100;
    }

    intArray += 1;
  }  
}  

void sortArray(const int nelem_in_array, int *array, int (*order)(int, int, int))
{
  for (i = 0; i < nelem_in_array; i++)
  {
    for (indx = 0; indx < (nelem_in_array - 1); indx++)
    {
      sflag = 0;

      if (!(*order)(sflag, *(array + indx) , *(array + (indx + 1))))
      {
        exchange((array + indx), (array + (indx + 1)));
      }
    }
  }
}      

void exchange(int *elem1, int *elem2)
{
  int tmp;

  tmp = *elem1;
  *elem1 = *elem2;
  *elem2 = tmp;
}

int ascending(int sflag, int n, int m)
{
  sflag = 0;

  if (m > n)
  {
   sflag = 1;
  }
  return sflag;
}

int decending(int sflag, int n, int m)
{
  sflag = 0;

  if (n > m)
  {
    sflag = 1;
  }
  return sflag;
}

float getAverage(int nelem_in_array, int *array) 
{
  sumElements(nelem_in_array, array);

  return (float)sum/nelem_in_array;
}


int sumElements(int nelem_in_array, int *array)
{
  sum = 0;

  for (indx = 0; indx < nelem_in_array; indx++)
  {
    sum += *array + indx;
  }
  return sum;
}