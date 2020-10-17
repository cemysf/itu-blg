/// BLG449E - MPI Graph Homework
/// Cem Yusuf Aydoğdu
/// 150120251
///
/// main.c
/// Contains main procedure for the program
///
/// Compiling:
/// mpicc -g -Wall -std=c99 -o out main.c -lm
///
/// Running:
/// mpiexec -n 10 ./out
///
/// NOTES:
/// Tested with 100 nodes(defined in graph.h) and number of processes as 10.
/// Makefile with the project contains necessary compiling and running commands
///

#include <mpi/mpi.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Number of nodes in the graph is defined as fixed
#define NODECOUNT 10

// Maximum distance from a node to another node, if there is a connection
#define MAXDIST 100

// Corresponds as no connection between two nodes
#define INF INT_MIN

typedef struct node
{
    // Identifier of the node
    int nodeNumber;

    // Contains distances to other nodes (edges)
    int distanceArray[NODECOUNT];

}Node;


/**
 * @brief initializeNode: Initialize the edges array of a node with 'no connection'
 * @param node
 */
void initializeNode(Node *node)
{
    int i;
    for(i=0; i<NODECOUNT; i++)
    {
        // Initialize edges
        node->distanceArray[i] = INF;
    }
}


/**
 * @brief setNodeNumber: Assigns node number to a node
 * @param node
 * @param number
 */
void setNodeNumber(Node *node, int number)
{
    node->nodeNumber = number;
}

/**
 * @brief getNodeNumber: Gets the node number of the node
 * @param node
 * @return nodeNumber
 */
int getNodeNumber(Node *node)
{
    return node->nodeNumber;
}

/**
 * @brief setDistance: Assigns distance from a node to another node
 * @param node
 * @param otherNodeNumber
 * @param distance
 */
void setDistance(Node *node, int otherNodeNumber, int distance)
{
    node->distanceArray[otherNodeNumber] = distance;
}

/**
 * @brief getDistance : Returns distance from given node to specified other node
 * @param node
 * @param otherNodeNumber
 * @return distance to specified node
 */
int getDistance(Node *node, int otherNodeNumber)
{
    return node->distanceArray[otherNodeNumber];
}


/**
 * @brief printGraph: Prints the edges of each node to the screen
 * @param nodeArray
 */
void printGraph(Node *nodeArray)
{
    int i, j, dist;
    for(i=0; i<NODECOUNT; i++)
    {
        for(j=0; j<NODECOUNT; j++)
        {
            dist = getDistance(&nodeArray[i],j);

            // If the distance from a node to another node is INF, it means
            // there is no connection from the node to another node
            if(dist != INF)
                printf("Distance from %d to %d: %d\n", i, j, dist);
            //else
            //    printf("No connection from %d to %d\n", i, j);
        }
    }
    printf("\n");
}


// Max message length for communications
const int MSGLEN = 1000;

/**
 * @brief checkDistances: Checks the given node, if the distance is found, writes
 * information to buffer
 * @param rank
 * @param node
 * @param distance
 */
void checkDistances(int rank, Node *node, int distance)
{
    char buffer[MSGLEN];
    strcpy(buffer, "");

    int i;
    for(i=0; i<NODECOUNT; i++)
    {
        if(getDistance(node, i) == distance)
        {
            char message[10];
            sprintf(message, "%d to %d\n", getNodeNumber(node), i);

            strcat(buffer, message);
        }
    }

    if(rank == 0)
    {
        printf("%s", buffer);

    }
    else
    {
        MPI_Send(buffer, strlen(buffer)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
}


int main()
{

    Node *nodes;
    int distance;       // Distance will be asked from the user, after initializing nodes

    /** Starting parallel programming with MPI **/
    int my_rank;
    int comm_size;

    // Initialize MPI
    MPI_Init(NULL, NULL);
    // Get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    // Get my rank
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Calculate number of nodes to each process
    int nodePerProcess = ceil(((double)NODECOUNT) / ((double)comm_size));

    // Prepare the node struct type for MPI
    int count=2;
    int lengths[2] = {1, NODECOUNT};

    MPI_Aint offsets[2] = {0, sizeof(int)};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};
    MPI_Datatype node_dataType;
    MPI_Type_struct(count, lengths, offsets, types, &node_dataType);
    MPI_Type_commit(&node_dataType);

    // Root initializes the graph
    if(my_rank == 0)
    {
        printf(" --- Process 0 --- \n");
        printf("Number of nodes: %d\n", NODECOUNT);
        printf("\n--- Initializing edges ---\n");

        nodes = (Node *)malloc(NODECOUNT * sizeof(Node));

        int i;
        for(i=0; i<NODECOUNT; i++)
        {
            setNodeNumber(&nodes[i], i);
            initializeNode(&nodes[i]);
        }

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

        // Print the edges of the graph
        printGraph(nodes);

        printf("\n--- End of edge initialization ---\n");

        // Ask user for distance
        printf("Enter distance: \n");
        scanf("%d", &distance);
    }

    // Temporary storage for each process
    Node temp;

    // Broadcast the distance to all processes
    MPI_Bcast(&distance,1,MPI_INT,0,MPI_COMM_WORLD);

    // Scatter the data from rank 0
    MPI_Scatter(nodes, nodePerProcess, node_dataType,
                &temp, nodePerProcess, node_dataType, 0, MPI_COMM_WORLD);

    checkDistances(my_rank, &temp, distance);


    if(my_rank == 0)
    {
        char message[MSGLEN];

        int i;
        for(i=1; i<comm_size; i++)
        {
            // Receive results
            MPI_Recv(message, MSGLEN, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", message);
        }

        free(nodes);
    }

    MPI_Finalize();


    return 0;
}
