/// BLG449E - MPI Graph Homework
/// Cem Yusuf Aydoğdu
/// 150120251
///
/// graph.h
/// Contains definitions about the graph structure
///
#ifndef GRAPH_H
#define GRAPH_H
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

#endif // GRAPH_H
