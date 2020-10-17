#include <mpi/mpi.h>
#include <stdio.h>

int main()
{
    int my_rank, comm_size;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Init structures
    MPI_Group group_world, group1, group2;
    MPI_Comm comm1, comm2;

    // Init ranks of groups
    int group1_ranks[]={0,1,3};
    int group2_ranks[]={0,2,4};
    // Get world group
    MPI_Comm_group(MPI_COMM_WORLD, &group_world);
    // Get new groups
    MPI_Group_incl(group_world, 3, group1_ranks, &group1);
    MPI_Group_incl(group_world, 3, group2_ranks, &group2);

    // CREATE NEW COMMUNICATORS!!!!!!!
    MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
    MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);





    ///test

    int data = 5, recv;
    if(my_rank == 0)
        data = 1;

    if(my_rank == 0 || my_rank == 1 || my_rank == 3)    ///!!!
    {
        MPI_Bcast(&data,1,MPI_INT,0,comm1);
        MPI_Reduce(&data,&recv,1,MPI_INT,MPI_MIN,0,comm1);
    }

    if(my_rank == 0)
        printf("send %d recv %d\n",data,recv);

    MPI_Finalize();
    return 0;
}
