#include <mpi/mpi.h>
#include <stdio.h>

int main()
{
    int my_rank, comm_size;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    MPI_Request req;
    MPI_Status status;
    int data = 4;

    int src_rank=0, dest_rank = 2;


    if(my_rank == src_rank)
    {
        data = my_rank;
        MPI_Isend(&data,1,MPI_INT, dest_rank,0,MPI_COMM_WORLD,&req);

        printf("unblockingly sent to %d\n", dest_rank);

        // testing nonblocking sending status
        int flag = 0;
        do
        {
            MPI_Test(&req, &flag, &status);

        }while(!flag);

        printf("confirmed sending..\n");

    }


    MPI_Finalize();
    return 0;
}
