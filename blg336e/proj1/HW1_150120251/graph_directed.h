/// BLG336E Project 1
/// Cem Yusuf Aydoğdu
/// 150120251

#ifndef GRAPH_DIRECTED_H
#define GRAPH_DIRECTED_H

#include "graph.h"

class Graph_directed:public Graph
{
public:

    // Reverse directed edges in the graph, returns that adjacency list
    adjList_dataStr reverseEdges();

    // Returns number of nodes reached from starting node
    int findNumberOfNodesReached(adjList_dataStr &adj_list, char start);

    // Check strong connectivity for directed graph
    void checkStrongConnectivity();

};

#endif // GRAPH_DIRECTED_H
