#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <stack>

using namespace std;

struct Edge
{
    string from;
    string to;

    int flow;
    int capacity;
};

typedef list<Edge> edgeList_datatype;
typedef map<string, edgeList_datatype> AdjList;

class Graph
{
    AdjList adj_list;

public:
    // Add a new node without edges
    void addNewNode(string &node_name);

    // Add a new node with an existing edge list
    void addNewNode(string &node_name, edgeList_datatype &edge_list);

    // Adds an edge from specified node
    void addEdgeToNode(string &node_name, Edge &edge);

    // Breath first search for Ford-Fulkerson algorithm (writes the path to provided path vector)
    void bfs(AdjList &adj, string &start_node, string &end_node, vector<Edge *> &path);

    // Augmenting path function for Ford Fulkerson algorithm
    int augmentPath(AdjList &adj, vector<Edge *> &path, string &assignment_string);

    // Ford Fulkerson algorithm to find solution (writes assignment to the given string)
    int fordFulkerson(string &assignment_string);

    // Output all in the adj matrix
    void printValuesToScreen();

    bool outputDotFile(string &filename);

};
#endif // GRAPH_H
