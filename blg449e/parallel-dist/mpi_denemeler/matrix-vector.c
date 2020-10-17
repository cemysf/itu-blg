#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAXRAND 10

///
/// |A0, A1, ...|       |B0|        |C0|
/// |...        |   *   |B1|    =   |C1|
/// |...        |       |..|        |..|
///
///
/// A matrixi tek boyutta olmalı!!


void printMatrices(int *A, int *A_dims, int *B, int *B_dims, int *C, int *C_dims)
{
    printf("A matrix: \t\t\t\tB: \t\tC:\n");

    int r;
    for(r=0; r<A_dims[0]; r++)
    {
        for(int c=0; c<A_dims[1]; c++)
        {
            printf("%d\t", A[r*A_dims[1] + c]);
        }
        printf("\t%d\t", B[r]);
        printf("\t%d\t", C[r]);
        printf("\n");
    }

    printf("\t\t\t\t");
    while(r < B_dims[0])
    {
        printf("\t%d\t", B[r]);
        printf("\n");

        r++;
    }
    printf("\n");
}



int main()
{
    int A_dims[2] = {3,4}, B_dims[2] = {4,1}, C_dims[2] = {3,1};     ///rastgele (ilki row ikinci col)

    srand(time(NULL));
    int my_rank, comm_sz;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int *A, *B, *C;

    // Rank0 is responsible for initializing
    if(my_rank == 0)
    {

        A = (int *)malloc(A_dims[0] * A_dims[1] * sizeof(int));
        B = (int *)malloc(B_dims[0] * sizeof(int));
        C = (int *)malloc(C_dims[0] * sizeof(int));

        // Init A
        for(int r=0; r<A_dims[0]; r++)
        {
            for(int c=0; c<A_dims[1]; c++)
            {
                int index = r*A_dims[1] + c;
                A[index] = rand() % MAXRAND;
            }
        }

        // Init B and C
        for(int c=0; c<B_dims[0]; c++)
        {
            B[c] = rand() % MAXRAND;
        }

        for(int c=0; c<C_dims[0]; c++)
        {
            C[c] = 0;
        }

        printMatrices(A, A_dims, B, B_dims, C, C_dims);

    }

    int *local_A = (int *)malloc(4 * sizeof(int));
    if(my_rank != 0)
        B = (int *)malloc(4*sizeof(int));

    int local_C = 0;


    // Scatter A row by row
    MPI_Scatter(A, 4, MPI_INT, local_A, 4, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter all B to each
    MPI_Bcast(B, 4, MPI_INT, 0, MPI_COMM_WORLD);

    /// Each proc calculates Cij
#pragma omp parallel for
    for(int i=0; i<4; i++)
    {
        //printf("(rank %d) A:%d B:%d \n", my_rank, local_A[i], B[i]);
        local_C += local_A[i] * B[i];
    }


    MPI_Gather(&local_C,1,MPI_INT, C,1,MPI_INT, 0, MPI_COMM_WORLD);



    free(local_A);
    free(B);

    if(my_rank == 0)
    {
        printf("\n--- After Calc ---\n");
        printMatrices(A, A_dims, B, B_dims, C, C_dims);

        free(A);free(C);
    }
    MPI_Finalize();
    return 0;
}
