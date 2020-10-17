#include <mpi/mpi.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int id;
    int value;
}Node;

int main()
{
    /// Init
    int my_rank;
    int comm_size;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    /// Prepare custom struct as a new MPI datatype
    int count=2;
    int lengths[2] = {1, 1};

    MPI_Aint offsets[2] = {0, sizeof(int)};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};
    MPI_Datatype node_dataType;
    MPI_Type_struct(count, lengths, offsets, types, &node_dataType);
    MPI_Type_commit(&node_dataType);


    Node n = { 0, 0 };
    if(my_rank == 0)
    {
        n.id = 4; n.value = 6;
    }

    MPI_Bcast(&n,1,node_dataType, 0,MPI_COMM_WORLD);

    Node *recv;
    if(my_rank==0)
    {
        recv = (Node*)malloc(sizeof(Node) * 10);
    }
    MPI_Gather(&n,1,node_dataType, recv,node_dataType,1, 0, MPI_COMM_WORLD);


    /// End
    MPI_Finalize();
    return 0;
}
