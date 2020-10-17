#include <stdio.h>
#include <mpi/mpi.h>

int ARRAY_DIM=2;

#define MSG_MAXLEN 50

int index(int row, int col)
{
    return (ARRAY_DIM*row + col);
}

int main(int argc, char *argv[])
{
    int my_rank, comm_sz;
    MPI_Init(NULL, NULL);

    // Init global ranks, comm size
    MPI_Comm_size (MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);


////////// Topoloji ayar başla /////////
    /// row1: (0 1)
    /// row2: (2 3)

    MPI_Group group_world;

    MPI_Group group1, group2;

    MPI_Comm comm_row1, comm_row2;

    int group1_ranks[2], group2_ranks[3];       /// ilk grupta: 0,1  ikinci grupta: 0,2,3 (0'dan 2 ve 3'e bcast gerek)

    // Arrange process lists
    group1_ranks[0] = 0;
    group1_ranks[1] = 1;

    group2_ranks[0] = 0;
    group2_ranks[1] = 2;
    group2_ranks[2] = 3;

    // Get group from MPI_COMM_WORLD
    MPI_Comm_group(MPI_COMM_WORLD, &group_world);

    // Create new groups
    MPI_Group_incl(group_world, 2, group1_ranks, &group1);
    MPI_Group_incl(group_world, 3, group2_ranks, &group2);

    // Create new communicators
    MPI_Comm_create(MPI_COMM_WORLD, group1, &comm_row1);
    MPI_Comm_create(MPI_COMM_WORLD, group2, &comm_row2);
////////// Topoloji ayar sonu /////////
/*    ///test başl///   /// çalışıyor ✓ ✓ ✓
    int data = my_rank, recv;

    if(my_rank == 0)
        data = 11;

    if(my_rank == 0 || my_rank == 1)        ///!!! sadece ilk rowdakiler kendi aralarında!!! (bunu kısıtlamayınca diğer rankler patlıyor)
    {
        MPI_Bcast(&data,1,MPI_INT,0, comm_row1);

        MPI_Reduce(&data,&recv,1,MPI_INT,MPI_SUM,0,comm_row1);
    }

    if(my_rank == 0)
    {
        printf("bcastted to first row, gathered from all: %d\n", recv);
    }
    /// test sonu ///   */



    double *a, *b, *c;
    double local_a, local_b, local_c;
    // Rank 0 initializes arrays
    if(my_rank == 0)
    {
        a = (double*) malloc(sizeof(double) * ARRAY_DIM * ARRAY_DIM);   //2d array, row*col
        b = (double*) malloc(sizeof(double) * ARRAY_DIM * ARRAY_DIM);   //2d array, row*col
        c = (double*) malloc(sizeof(double) * ARRAY_DIM * ARRAY_DIM);   //2d array, row*col

        a[index(0,0)] = 2.4;
        a[index(0,1)] = 3.5;
        a[index(1,0)] = 5.7;
        a[index(1,1)] = 1.2;

        b[index(0,0)] = 0.4;
        b[index(0,1)] = 2.1;
        b[index(1,0)] = 3.2;
        b[index(1,1)] = 5.4;

        c[index(0,0)] = c[index(0,1)] = c[index(1,0)] = c[index(1,1)] = 0.0;

    }


    /////////// STAGE 0 //////////////
    if(my_rank == 0)
        local_a = a[index(0,0)];
    // Bcast A00 to first row
    if(my_rank == 0 || my_rank == 1)        ///!!! sadece ilk rowdakiler kendi aralarında!!! (bunu kısıtlamayınca diğer rankler patlıyor)
    {
        MPI_Bcast(&local_a,1,MPI_DOUBLE,0, comm_row1);
    }

    if(my_rank == 0)
        local_a = a[index(1,1)];
    // Bcast A11 to second row
    if(my_rank == 0 || my_rank == 2 || my_rank == 3)
    {
        MPI_Bcast(&local_a,1,MPI_DOUBLE,0,comm_row2);       ///!!!!: rank0, kendisinin dahil olmadığı bir comm'a bcast yaparken patlıyor!!!
    }

    // Bcast Bij to all
    MPI_Scatter(b,1,MPI_DOUBLE, &local_b,1,MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Calc Cij
    local_c = local_a * local_b;


    /// test
    MPI_Gather(&local_c,1,MPI_DOUBLE, c,1,MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(my_rank == 0)
    {
        for(int i=0; i<ARRAY_DIM*ARRAY_DIM; i++)
            printf("C[%d] = %.4f \n", i, c[i]);
    }



    MPI_Finalize();

    return 0;
}

