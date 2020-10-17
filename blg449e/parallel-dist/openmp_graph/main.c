/// BLG449E - OpenMP Graph Homework
/// Cem Yusuf Aydoğdu
/// 150120251
///
/// main.c
/// Contains main procedure for the program
///
/// Compiling:
/// gcc main.c -o out -fopenmp -g -lm
///
/// Running:
/// ./out
///
#include <stdio.h>
#include <omp.h>
#include <limits.h>

// Number of threads
#define THREADCOUNT 10
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


/**
 * @brief checkDistance: Distance checking function for every thread
 * @param node
 * @param distance
 */
void checkDistance(Node *node, int distance)
{
    int i;
    for(i=0; i<NODECOUNT; i++)
    {
        if(getDistance(node, i) == distance)
        {
            printf("%d to %d\n", getNodeNumber(node), i);
        }
    }
}

int main()
{
    omp_set_num_threads(THREADCOUNT);

    printf("Number of nodes: %d\n", NODECOUNT);
    printf("Number of threads: %d\n", THREADCOUNT);
    printf("\n--- Initializing edges ---\n");

    // Initialize node array
    Node nodes[NODECOUNT];
    int i;
    #pragma omp parallel
    {
        for(i=0; i<NODECOUNT; i++)
        {
            setNodeNumber(&nodes[i], i);
            initializeNode(&nodes[i]);
        }
    }
    // Assign edges of nodes randomly
    srand(time(NULL));
    int loopSize = rand() % (NODECOUNT*NODECOUNT);
    int node1, node2, dist;

    // Execute loop in parallel
    #pragma omp parallel
    {
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
    }

    // Print the edges of the graph
    printGraph(nodes);

    printf("\n--- End of edge initialization ---\n");

    // Ask user for distance
    int distance;
    printf("Enter distance: \n");
    scanf("%d", &distance);

    // Parallel part of the code
    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        // A node for each thread
        checkDistance(&nodes[id], distance);
    }

    return 0;
}
