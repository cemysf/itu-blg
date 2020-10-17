/// BLG336E Project 1
/// Cem Yusuf Aydoğdu
/// 150120251

#include "graph_undirected.h"

int Graph_undirected::findNumberOfShortestPaths(char start, char end)
{
    // Cast characters as indexes
    int startNode = (int)start - 65;
    int endNode = (int)end - 65;

    // If start and end is same node, return 1
    if(startNode == endNode)
        return 1;

    // Initialize discovered array
    bool discovered[nodeCount];
    for(int i=0; i<nodeCount; i++)
        discovered[i]=false;
    discovered[startNode]=true;

    // Initialize layers
    list<int> layers[nodeCount-1];
    layers[0].push_back(startNode);

    // Layer counter
    int i = 0;
    int j = startNode;

    // Path counter
    int pathCount = 0;

    // Minimum path lenght assumed as maximum initially
    int pathLen = numeric_limits<int>::max();

    while(!layers[i].empty())
    {
        j = layers[i].front();
        layers[i].pop_front();

        for(connection_dataStr::iterator it2 = adjList[j].begin(); it2 != adjList[j].end(); it2++)
        {
            if(discovered[*it2] == false)
            {
                discovered[*it2] = true;
                layers[i+1].push_back(*it2);
            }

            if(*it2 == endNode && (i+1) <= pathLen)
            {
                pathLen = i+1;
                pathCount += 1;
            }
        }

        // Go to next layer if checked all
        if(layers[i].empty())
            i+= 1;
    }

    return pathCount;
}

void Graph_undirected::findEdges(map<pair<int, int>, int > edges)
{
    int i = 0;
    for( adjList_dataStr::const_iterator it = adjList.begin(); it != adjList.end(); it++)
    {
        for( connection_dataStr::const_iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            // In order to not rewrite same edges, add edges as (m,n) where m < n
            if( i < *it2)
            {
                edges.insert (pair<pair<int,int>,int>(make_pair(i,*it2),0));
            }
        }
        i++;
    }
}


void Graph_undirected::getPath(char start, char end, vector<int> &path)
{

    // Cast characters as indexes
    int startNode = (int)start - 65;
    int endNode = (int)end - 65;


    // If start and end is same node, retur
    if(startNode == endNode)
        return;

    // Initialize discovered array
    bool discovered[nodeCount];

    // init previous array
    int previous[nodeCount];

    for(int i=0; i<nodeCount; i++)
    {
        discovered[i]=false;
        previous[i]=-1;
    }
    discovered[startNode]=true;

    // Initialize layers
    list<int> layers[nodeCount-1];
    layers[0].push_back(startNode);

    // Layer counter
    int i = 0;
    int j = startNode;


    bool found = false;
    while(!found)
    {
        j = layers[i].front();
        layers[i].pop_front();

        for(connection_dataStr::iterator it2 = adjList[j].begin(); it2 != adjList[j].end(); it2++)
        {
            if(discovered[*it2] == false)
            {
                discovered[*it2] = true;
                layers[i+1].push_back(*it2);
                previous[*it2] = j;
            }

            if(*it2 == endNode)
            {
                found = true;
                break;
            }

        }

        // Go to next layer if checked all
        if(layers[i].empty())
            i+= 1;
    }

    // Initialize a temporary stack for path
    stack<int> temp_stack;
    temp_stack.push(endNode);
    i = previous[endNode];
    while( i != startNode)
    {
        temp_stack.push(i);
        i = previous[i];
    }
    temp_stack.push(startNode);


    while(!temp_stack.empty())
    {
        path.push_back(temp_stack.top());
        temp_stack.pop();
    }

}

void Graph_undirected::computeBetweenness()
{
    // Find edges in the graph, with a counter for each edge
    map<pair<int,int>, int> edges;
    findEdges(edges);


    vector<vector<int> > paths;

    // From each node to another nodes, find shortest paths
    for(int i=0; i<nodeCount; i++)
    {
        for(int j=i+1; j<nodeCount; j++)
        {
            vector<int> current_path;
            getPath((char)(i+65), (char)(j+65), current_path);
            paths.push_back(current_path);
        }
    }


    // Traverse each path in all paths
    for(int i=0; i<paths.size(); i++)
    {
        vector<int> &current_path = paths[i];
        for(int k=0; k<current_path.size()-1; k++)
        {
             //Increment the counter for edge (m,n)
             int m = current_path[k], n = current_path[k+1];
             if(m<n)
                edges[make_pair(m,n)] += 1;
             else
                 edges[make_pair(n,m)] += 1;
        }
    }


    // Print counts of edges
    for(map<pair<int, int>, int >::const_iterator it=edges.begin(); it!=edges.end(); it++)
    {
        cout << "Edge (" << (char)(it->first.first+65) << "," << (char)(it->first.second+65) << "), betweenness = " << it->second << endl;
    }

}
