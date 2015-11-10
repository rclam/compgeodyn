#include <cstdio>
using namespace std;
#include <cstdlib>
using namespace std;
#include <iostream>
using namespace std;

class arrayCopier
{
  public:

    double *copyArray(int nelem_in_array, double *array2Bcopied, double *copied2Array)
    {
      int index;
      double *ptr;

      ptr = copied2Array;
       
      for (index = 0; index < nelem_in_array; index++)
      {
        *ptr = array2Bcopied[index];

        if (index < (nelem_in_array - 1))
        {
          ptr++;
        }
      }
 
      return ptr;
    }

    void printArray(int nelem_in_array, double *array2Bprinted)
    {
      int index;

      cout << '\n';
      cout << "The elements copied from the original array to the new array are [  ";

      for (index = 0; index < nelem_in_array; index++)
      {
        cout << *array2Bprinted << "  ";
        array2Bprinted++;
      }

      cout << "]" << '\n';
      cout << '\n';
    }
};  


int main(int argc, char *argv[])
{
  int nelem, index;
  double *origArray, *newArray;

// Instantiate a pointer to an arrayCopier object
  arrayCopier *cpy = new arrayCopier; 

// Set number of elements in array
  nelem = 5;
  
// Dynamically allocate memory for each array
  origArray = new double[nelem];
  newArray = new double[nelem];

// Initialize array that is to be copied
  for (index = 0; index < nelem; index++)
  {
    origArray[index] = (index + 1);
  }

// Copy the original array to the new array
  newArray = (cpy -> copyArray(nelem, origArray, newArray));

// Print the elements of the new array
  cpy -> printArray(nelem, newArray);

  delete[] origArray;
  delete[] newArray;

    return 0;
}