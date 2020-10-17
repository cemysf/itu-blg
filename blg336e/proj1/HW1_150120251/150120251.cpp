/// BLG336E Project 1
/// Cem Yusuf Aydoğdu
/// 150120251

#include "graph.h"
#include "graph_undirected.h"
#include "graph_directed.h"

using namespace std;

int main()
{
    string filenames[] = {"input1.txt", "input2.txt"};

    Graph_undirected g;
    g.readAdjMatrix(filenames[0]);

    // Question a
    cout << "Shortest paths:" << endl;
    cout << "Number of shortest paths, A to F is " << g.findNumberOfShortestPaths('A','F') << endl;
    cout << "Number of shortest paths, E to G is " << g.findNumberOfShortestPaths('E','G') << endl;
    cout << "Number of shortest paths, B to F is " << g.findNumberOfShortestPaths('B','F') << endl;
    cout << endl;

    // Question b
    cout << "Betweenness:" << endl;
    g.computeBetweenness();
    cout << endl;


    Graph_directed u;
    u.readAdjMatrix(filenames[1]);

    // Question c
    cout << "Connectivity:" << endl;
    u.checkStrongConnectivity();
    cout << endl;

    return 0;
}
