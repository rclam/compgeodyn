/*
!**********************************************************************
!     matmult.c - simple matrix multiply implementation 
!************************************************************************
*/

// ! try changing this value to 2000 to get rid of transient effects ! at startup

#include <stdio.h>
#define SIZE_OF_MATRIX 500
#define a(i,j)  a[ (i-1) + (j-1)*SIZE_OF_MATRIX ]
#define b(i,j)  b[ (i-1) + (j-1)*SIZE_OF_MATRIX ]
#define c(i,j)  c[ (i-1) + (j-1)*SIZE_OF_MATRIX ]
#include <mpi.h>
#include <unistd.h>


void initialize(double *a, double *b, int n);
void multiply_matrices(double *answer, double *buffer, double *b, int matsize);

int main(int argc, char *argv[]){
  // ! try changing this value to 2000 to get rid of transient effects ! at startup
  double a[SIZE_OF_MATRIX*SIZE_OF_MATRIX] ;
  double b[SIZE_OF_MATRIX*SIZE_OF_MATRIX] ;
  double c[SIZE_OF_MATRIX*SIZE_OF_MATRIX] ;
  double  buffer[SIZE_OF_MATRIX], answer[SIZE_OF_MATRIX] ;
  double  one = 1.0;
  
  MPI_Status status;
  int myid, master, maxpe, ierr;
  int i, j, numsent, sender  ;
  int answertype, row, flag ;
  int matsize ;
  
  ierr = MPI_Init( &argc, &argv );
  ierr = MPI_Comm_rank( MPI_COMM_WORLD, &myid  );
  ierr = MPI_Comm_size( MPI_COMM_WORLD, &maxpe );
  printf("Process %4d of %4d\n", myid, maxpe     );
  
  master = 0;
  matsize = SIZE_OF_MATRIX;
  
  if ( myid == master ){
    //! master initializes and then dispatches 
    //! initialize a and b 
    initialize(a, b, matsize);
    numsent = 0;

    //! send b to each other process 
    for(i=1;i<=matsize;i++){
      ierr = MPI_Bcast(&b(1,i), matsize, MPI_DOUBLE, master, MPI_COMM_WORLD); 
    }
    
    //! send a row of a to each other process; tag with row number 
    for(i=1;i<=maxpe-1;i++){
      for(j=1;j<=matsize;j++){
	buffer[j-1] = a(i,j);
      }
      ierr=MPI_Send(buffer, matsize, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
      numsent = numsent + 1; 
    }
    
    for(i=0;i<matsize;i++){ 
      ierr = MPI_Recv(answer, matsize, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      sender     = status.MPI_SOURCE;
      answertype = status.MPI_TAG; 
      for(j=1;j<=matsize;j++){
	c(answertype,j) = answer[j-1]; 
      }
      
      if (numsent < matsize){
	for(j=1;j<=matsize;j++){ buffer[j-1] = a(numsent+1,j); }
	ierr = MPI_Send(buffer, matsize, MPI_DOUBLE, sender, numsent+1, MPI_COMM_WORLD) ;
	numsent = numsent+1;
      }
      else{
	ierr = MPI_Send(&one, 1, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD); 
      }
    }
    
    //! print out one element of the answer
    printf("c(%d,%d) = %f\n", matsize,matsize,c(matsize,matsize) );
  }
  else{ 
    //! workers receive B, then compute rows of C until done message 
    for(i=1;i<=matsize;i++){
      ierr=MPI_Bcast(&b(1,i), matsize, MPI_DOUBLE, master, MPI_COMM_WORLD);
    }

    flag = 1;
    while (flag != 0){
      ierr = MPI_Recv(buffer, matsize, MPI_DOUBLE, master, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      row = status.MPI_TAG; 
      flag = row;
      if (flag != 0){
	// multiply the matrices here using C(i,j) += sum (A(i,k)* B(k,j))
	multiply_matrices(answer, buffer, b, matsize);
	ierr = MPI_Send(answer, matsize, MPI_DOUBLE, master, row, MPI_COMM_WORLD);
      }
    }
  }
  
  ierr = MPI_Barrier(MPI_COMM_WORLD);
  ierr = MPI_Finalize();
  
  return 0;
}

void initialize(double *a, double *b, int n){
   int i, j;

   for(i=1;i<=n;i++) for(j=1;j<=n;j++) a(j,i) = i ;
   for(i=1;i<=n;i++) for(j=1;j<=n;j++) b(j,i) = i ;
}
      
void multiply_matrices(double *answer, double *buffer, double *b, int matsize){
   int i, j;
   // Multiply the row with the column 
   for(i=1;i<=matsize;i++){
     answer[i-1] = 0.0;
     for(j=1;j<=matsize;j++){
        answer[i-1] = answer[i-1] + buffer[j-1]*b(j,i); 
     }
   }
}
