#include <stdio.h>
#include <mpi/mpi.h>
#include <string.h>

const int MSG_MAXLEN = 100;

int main()
{
    char message[MSG_MAXLEN];

    int my_rank;
    int comm_size;      // number of processes

    // Initialize MPI
    MPI_Init(NULL, NULL);
    // Get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    // Get my rank
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    MPI_Barrier(MPI_COMM_WORLD);        ///gerek yok, denemek için
    if(my_rank != 0)
    {
        sprintf(message, "hallo from process %d of %d\n", my_rank, comm_size);
        // Other ranks send messsage to rank0
                // void *, int len, MPI_Datatype, int dest, int tag, MPI_Comm
        MPI_Send(message, strlen(message)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else {
        printf("comm size: %d\n", comm_size);
        printf("hallo from process %d of %d\n",my_rank, comm_size);

        MPI_Status status;
        int n;

        for(int q = 1; q<comm_size; q++)
        {
            // Rank 0  receives the messages
            MPI_Recv(message, MSG_MAXLEN, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("%s", message);

            // Print info about status

            MPI_Get_count(&status, MPI_CHAR, &n);
            printf("getcount: error:%d source:%d tag:%d _cancelled:%d _ucount:%d \n\n", status.MPI_ERROR, status.MPI_SOURCE, status.MPI_TAG, status._cancelled, status._ucount);
        }
    }


    MPI_Finalize();
    return 0;
}
