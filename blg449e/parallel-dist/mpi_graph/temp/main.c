/// BLG449E - MPI Graph Homework
/// Cem Yusuf Aydoğdu
/// 150120251
///
/// main.c
/// Contains main procedure for the program
///

#include <mpi/mpi.h>

// Definitions of the graph is from a header file
#include "graph.h"

int main()
{
    /** Initializing the graph **/
    // Initialize nodes
    Node nodes[NODECOUNT];

    int i;
    for(i=0; i<NODECOUNT; i++)
        initializeNode(&nodes[i]);

    // Assign edges of nodes randomly
    srand(time(NULL));
    int loopSize = rand() % (NODECOUNT*NODECOUNT);
    int node1, node2, dist;

    // Randomly selected loop count
    for(i=0; i<loopSize; i++)
    {
        // Randomly select two nodes
        node1 = rand()%NODECOUNT;
        node2 = rand()%NODECOUNT;

        // If two randomly selected nodes are same, try again
        if(node1 == node2)
            continue;

        // Randomly assign distance from a node to another node
        dist = rand() % (MAXDIST);

        // Assuming the graph is directed, only specified direction is assigned
        setDistance(&nodes[node1], node2, dist);
    }

    printf("Number of nodes: %d\n", NODECOUNT);
    printf("\n--- Initialized edges ---\n");

    // Print the edges of the graph
    printGraph(nodes);

    /** End of graph initialization**/




    /** Starting parallel programming with MPI **/
    int my_rank;
    int comm_size;

    // Initialize MPI
    MPI_Init(NULL, NULL);
    // Get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    // Get my rank
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);





    MPI_Finalize();

    // Delete edge arrays in nodes
    for(i=0; i<NODECOUNT; i++)
        deleteNode(&nodes[i]);

    return 0;
}
