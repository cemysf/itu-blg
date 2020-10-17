/// BLG449E - MPI Graph Homework
/// Cem Yusuf Aydoğdu
/// 150120251
///
/// graph.c
/// Contains functions about graph structure
///

#include "graph.h"

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
