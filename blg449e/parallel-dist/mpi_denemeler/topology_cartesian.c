#include <mpi/mpi.h>
#include <stdio.h>

int main()
{
    int my_rank, comm_size;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    int rows=2, cols=2;     ///// process sayısı rows*cols olmalı!!
    int dim[2] = {cols, rows};
    int period[2] = {1, 1};     /// (bool) both rows and cols are cyclic
    int reorder = 1;            /// (bool) rank reordering

    MPI_Comm comm_cart;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm_cart);


    /// Find coords of given rank

    int coords[2];
    if(my_rank == 5)
    {
        MPI_Cart_coords(comm_cart, my_rank, 2, coords);     /// returns cartesian coordinates of given rank


        printf("my rank is %d, coords in cartesian: %d,%d \n", my_rank, coords[0], coords[1]);
    }


    /// Find rank of given coords

    if(my_rank == 0)
    {
        int id;
        coords[0] = 2, coords[1] = 3;

        for(int i=0; i<=rows; i++)
        {
            for(int j=0; j<=cols; j++)
            {
                coords[0] = i, coords[1] = j;

                MPI_Cart_rank(comm_cart, coords, &id);         /// returns rank of the given coords

                printf("rank %d is at %d,%d \n",id, coords[0], coords[1]);
            }
        }

    }


    ///!!! Every process gets its row and column communicator !!!
    MPI_Comm comm_row, comm_col;
    int varying_dims[2];      /// (bool) allow row or col to vary (0,1 for row comm; 1,0 for col comm)

    varying_dims[0] = 0;
    varying_dims[1] = 1;
    MPI_Cart_sub(comm_cart, varying_dims, &comm_row);

    varying_dims[0] = 1;
    varying_dims[1] = 0;
    MPI_Cart_sub(comm_cart, varying_dims, &comm_col);



//    /// !!! MPI_Cart_Shift returns correct ranks to shift data !!!
    int left_right[2], up_down[2];
    if(my_rank == 1)
    {
        MPI_Cart_shift(comm_cart, 0, 1, &my_rank, left_right);
        MPI_Cart_shift(comm_cart, 1, 1, &my_rank, up_down);

        printf("(rank %d)my neighbours ranks: left:%d right:%d up:%d down:%d \n", my_rank, left_right[0], left_right[1], up_down[0], up_down[1]);
    }



    MPI_Finalize();
    return 0;
}
