/// BLG336E Project 1
/// Cem Yusuf Aydoğdu
/// 150120251

#include "graph_directed.h"

adjList_dataStr Graph_directed::reverseEdges()
{
    adjList_dataStr reversed;

    connection_dataStr adj[nodeCount];
    int i = 0;
    for( adjList_dataStr::const_iterator it = adjList.begin(); it != adjList.end(); it++)
    {
        for( connection_dataStr::const_iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            adj[*it2].push_back(i);
        }
        i++;
    }

    for(int i = 0; i<nodeCount; i++)
        reversed.push_back(adj[i]);
    return reversed;
}

int Graph_directed::findNumberOfNodesReached(adjList_dataStr &adj_list, char start)
{
    // Cast start char as index
    int startNode = (int)start - 65;

    // Initialize discovered array
    bool discovered[nodeCount];
    for(int i=0; i<nodeCount; i++)
        discovered[i]=false;
    discovered[startNode]=true;

    // Initialize layers
    list<int> layers[nodeCount];
    layers[0].push_back(startNode);

    // Layer counter
    int i = 0;
    int j = startNode;

    // Number of found node
    int reachedNodeCount = 0;

    while(!layers[i].empty())
    {
        j = layers[i].front();
        layers[i].pop_front();

        for(connection_dataStr::iterator it2 = adj_list[j].begin(); it2 != adj_list[j].end(); it2++)
        {
            if(discovered[*it2] == false)
            {
                discovered[*it2] = true;
                layers[i+1].push_back(*it2);
                reachedNodeCount += 1;
            }
        }

        // Go to next layer if checked all
        if(layers[i].empty())
            i+= 1;
    }

    return reachedNodeCount;
}

void Graph_directed::checkStrongConnectivity()
{
    srand(time(NULL));
    int randomNode = rand() % nodeCount;
    adjList_dataStr reversedList = reverseEdges();

    int reachCount = findNumberOfNodesReached(adjList, (char)(randomNode+65));
    int reachCount_reversed = findNumberOfNodesReached(reversedList, (char)(randomNode+65));

    if( (reachCount == (nodeCount-1)) && (reachCount_reversed == (nodeCount-1)))
        cout << "Strongly connected" << endl;
    else
        cout << "Not strongly connected" << endl;
}
