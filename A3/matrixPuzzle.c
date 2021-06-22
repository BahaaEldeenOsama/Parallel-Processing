#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
     int i,j;
     const int row = 6;
     const int col = 5;
     char *matrix[6][5]={{"X", "O", "X","X", "X"},
                         {"X", "O", "X","O", "X"},
                         {"O", "X", "O","O", "X"},
                         {"X", "X", "X","X", "X"},
                         {"X", "O", "O","X", "X"},
                         {"O", "X", "O","X", "O"}};

    printf("\n Intput : \n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {

            printf("%s ",matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");

   #pragma omp parallel private(i, j)
   {
    #pragma omp for
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if( matrix[i][j] == "O" && (matrix[i][j-1] == "X" && matrix[i][j+1] == "X" ) && j!=0  && j!=col-1   )
             {
                    matrix[i][j] = "X";
             }
        }
    }
   }
    
    printf("\n Output : \n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {

            printf("%s ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");


       return 0;
}
