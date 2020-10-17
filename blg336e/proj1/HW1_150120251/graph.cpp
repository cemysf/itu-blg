/// BLG336E Project 1
/// Cem Yusuf Aydoğdu
/// 150120251

#include "graph.h"

Graph::Graph()
{
    nodeCount = 0;
}

Graph::~Graph ()
{

}

void Graph::readAdjMatrix(string filename)
{
    ifstream file(filename.c_str(), ios::in);
    if(!file.is_open())
    {
        cout << "File error: cannot open " << filename << endl;
        return;
    }

    // Find number of nodes
    string line;
    while(getline(file, line))
        nodeCount += 1;
    file.clear();
    file.seekg(0);

    // Read file line by line
    string temp;
    int c1=0, c2=0;
    while(getline(file, line))
    {

        stringstream ss(line);

        // Adjacency list of current line
        list<int> adj;

        // Parse the current line
        while(ss >> temp)
        {
            if(temp.find('1') == 0)
            {
                adj.push_back(c2);
            }
            c2 += 1;
        }
        c2 = 0;
        c1++;

        // Add connections from current node to another nodes
        adjList.push_back(adj);
    }

    file.close();
}

