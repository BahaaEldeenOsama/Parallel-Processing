#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>

double fun(int i){

      return  (double)1.0/pow(2,i); 
}

int main (int argc , char * argv [])
{
   
    int n=0 ;
    int myRank ;
    int numprocs; 
    int i ;
    double sum=0.0 , allSum=0.0,x=0.0,res=0.0,error=0.0;
    MPI_Init (& argc ,& argv );
    MPI_Comm_size ( MPI_COMM_WORLD ,& numprocs );
    MPI_Comm_rank ( MPI_COMM_WORLD ,& myRank );
    
    for(;;)
   {
      if(myRank==0){
          printf("Enter value of n : ");
         scanf ( "%d" ,& n );  
       }
       MPI_Bcast (&n , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
       
      if ( n == 0){
           break ; 
      }   
      else
     {
        res= 0.0; 
        sum = 0.0;   
        #pragma omp parallel for reduction (+: sum ) private (i)
         for ( i = myRank + 1; i <= n ; i += numprocs ) 
         {    
		sum += fun(i);
         }
          
         res = sum;
         MPI_Reduce (&res , &allSum , 1 , MPI_DOUBLE , MPI_SUM , 0 , MPI_COMM_WORLD );   
         
         if(myRank==0){
              
              error = 1-allSum;
              printf("\n");
              printf("*******************************");
              printf("\n");
              printf("calculated : %.16f \n",allSum);
              printf("Error      : %.16f \n", error );
              printf("*******************************") ;
              printf("\n");

         }
     } 
   }
    
    MPI_Finalize ();
    return EXIT_SUCCESS ;


}
