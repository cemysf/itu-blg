#include<stdio.h>
#include<mpi/mpi.h>

#include<stdlib.h>
int main(int argc, char *argv[])
{
    int my_rank;
    int comm_size;      // number of processes

    int data = -1;
    int recv;

    // Initialize MPI
    MPI_Init(NULL, NULL);
    // Get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    // Get my rank
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank == 0)
        data = 2;


//    // bcast new data
//    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
//    /// check bcast
//    if(my_rank != 0)
//    {
//        MPI_Send (&data,1,MPI_INT,0,0,MPI_COMM_WORLD);
//    }
//    else
//    {
//        for(int q=1; q<comm_size; q++)
//        {
//        MPI_Recv (&recv,1,MPI_INT,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
//        printf("received %d from %d\n   ", recv, q);
//        }
//    }



    /// Scatter ///
    int *arr;
    if(my_rank == 0)
    {
        arr =(int*) malloc(sizeof(int) * comm_size);
        for(int i=0; i<comm_size; i++)
            arr[i] = i;
    }
    MPI_Scatter (arr,1,MPI_INT,&data,1,MPI_INT,0,MPI_COMM_WORLD);
    //free(arr);


    data = 55;

    MPI_Gather(&data,1,MPI_INT, arr,1,MPI_INT, 0, MPI_COMM_WORLD);


    if(my_rank==0)
    {
        printf("gathered: \n");
        for(int i=0; i<comm_size; i++)
            printf("%d ", arr[i]);
    }



//    /// Reduce ///
//    MPI_Reduce(&data, &recv, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//    if(my_rank == 0)
//    {
//        printf("recv: %d\n",recv);

//    }



    MPI_Finalize ();
    return 0;
}
