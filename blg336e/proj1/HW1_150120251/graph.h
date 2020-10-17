/// BLG336E Project 1
/// Cem Yusuf Aydoğdu
/// 150120251

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <queue>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stack>
#include <map>

using namespace std;

// Data structure for connections from a node to another nodes
typedef list<int> connection_dataStr;

// Data structure for adjacency list
typedef vector <connection_dataStr> adjList_dataStr;

class Graph
{
protected:
    int nodeCount;

    // Adjacency List
    adjList_dataStr adjList;

public:
    Graph();
    ~Graph();

    // Reads the matrix from file and creates an adjacency list
    void readAdjMatrix(string filename);

};





#endif // GRAPH_H
