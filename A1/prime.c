#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define  True 1
#define  False 0
 


int IsPrime(int n)
{   
    if(n==2){
          return True;
    }
    if(n<2){
        return False;
    }
    for(int i=2;i<n;++i){
        if( n%i == 0 ){
            return False;
        }
    }
  
 return True;
}


 
int CountPrimes(int start, int end) {
	int cnt = 0;
	int i;
	for(i = start; i <= end; i++) {
		if(IsPrime(i)) {
				cnt++;
		}
	}
	return cnt;
}



int taskDivision(int NumProcesses, int rang) {
	
	int buffLimit = rang;
	int divMaster = 0;

	if(NumProcesses > 0) {
		divMaster = rang / NumProcesses;
		buffLimit -= divMaster;

                int i;
		for(i = 1; i < NumProcesses; i++) 
               {
			int div = rang / NumProcesses;
			buffLimit -= div;
			if(buffLimit != 0 && i == (NumProcesses - 1)) {
				div += buffLimit;
			}
			MPI_Send(&div, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	return divMaster;
}

int main (int argc, char* argv[]) {
	int rank; 
        int NumProcesses;
	int Lowerbound;
	int Upperbound;
	int taskEnd;
	int taskStart;
	int range;
	int taskSize;
	int NumOfPrime = 0;
	MPI_Status status;

	Upperbound = atoi(argv[2]);
	Lowerbound = atoi(argv[1]);
	range = Upperbound - Lowerbound  ;  

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &NumProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) 
        {
		taskSize = taskDivision(NumProcesses, range);
		taskStart = Lowerbound;
	
        }
        else
       {
		int divRecv;
		MPI_Recv(&divRecv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		taskSize = divRecv;
		taskStart = Lowerbound + (range / NumProcesses) * rank;
	}

	taskEnd = taskStart + taskSize - 1 ;  
	NumOfPrime = CountPrimes(taskStart, taskEnd );
        
	printf("Total number of prime numbers in p%d is : %d \n", rank, NumOfPrime);

	if(rank != 0) {
		MPI_Send(&NumOfPrime, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		
	} 
        else 
        {
                
                // This is master .
                // collect the processes . 
                int i;
		int totalPrimesFound = NumOfPrime;
		for(i = 1; i < NumProcesses; i++) 
                {
			int recvFound = 0;
			MPI_Recv(&recvFound, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			totalPrimesFound += recvFound;
		}	 
                printf("*******************************************\n");
		printf("Total number of prime numbers is: %d \n", totalPrimesFound);

	}

	MPI_Finalize();

	return 0;
}
