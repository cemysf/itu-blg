/// BLG336E Project 1
/// Cem Yusuf Aydoğdu
/// 150120251

#ifndef GRAPH_UNDIRECTED_H
#define GRAPH_UNDIRECTED_H

#include "graph.h"

class Graph_undirected : public Graph
{
public:

    // Returns number of shortest paths from start to end node
    int findNumberOfShortestPaths(char start, char end);

    // Finds the edges in the graph, writes to given container
    void findEdges(map<pair<int, int>, int > edges);

    // Finds a shortest path from a node to another node, writes the path to container
    void getPath(char start, char end, vector<int> &path);

    // Compute and print betweenness of all edges
    void computeBetweenness();
};

#endif // GRAPH_UNDIRECTED_H
