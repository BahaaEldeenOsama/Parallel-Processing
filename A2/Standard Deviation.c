#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int my_rank;
    int NumProcesses;
    int n;
    int i;
    int localSum = 0;
    int allSum;
    int arr[100000];
    int rand_val; 
    double global_Mean=0.0;
    double Final_Mean=0.0;
    double allSum2=0.0;
    double Final_Sum=0.0;
    double res=0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &NumProcesses);


    ///Master
    if(my_rank == 0){
    printf("Enter number of elements per each process : ");
    scanf("%d", &n);
    printf("\n");
    }

    memset(arr, 0, n*sizeof(arr[0]));
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
      
    srand(time(0));
    for(i=0; i<n; i++){
    
        rand_val = (rand() % 100) + 1 ;
        printf("value :%d ", rand_val);
        printf("\n");
        localSum += rand_val;
        arr[i] = rand_val;
    }

     MPI_Allreduce(&localSum, &allSum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
     global_Mean = (double) allSum / ( n * NumProcesses);
    
    for(i=0; i<n; i++){

        allSum2 +=  pow( (arr[i] - global_Mean) , 2 );
    }

    MPI_Reduce(&allSum2, &Final_Sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(my_rank == 0)
    {
        Final_Mean = (double)Final_Sum/(n * NumProcesses);
        res = sqrt(Final_Mean);
        printf("\n");
        printf("Result : %f ", res);
        printf("\n");
         
    }

    MPI_Finalize();
    return 0;
}
