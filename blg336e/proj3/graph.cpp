/// BLG336E Analysis of Algorithms 2
/// Project 3
///
/// Cem Yusuf Aydoğdu
/// 150120251

#include "graph.h"

void Graph::addNewNode(string &node_name)
{
    edgeList_datatype edge;
    adj_list[node_name] = edge;
}


void Graph::addNewNode(string &node_name, edgeList_datatype &edge_list)
{
    adj_list[node_name] = edge_list;
}

void Graph::addEdgeToNode(string &node_name, Edge &edge)
{
    AdjList::iterator it =adj_list.find(node_name);
    if(it != adj_list.end())
    {
        it->second.push_back(edge);
    }
    else
    {
        cout << "Node " << node_name << " not found!" << endl;
    }
}

void Graph::bfs(AdjList &adj, string &start_node, string &end_node, vector<Edge *> &path)
{
    // Initialize visited list and previous node list
    map<string, bool> discovered;
    map<string, Edge *> previous;
    for(AdjList::const_iterator it = adj.begin(); it!=adj.end(); it++)  //O( |adj_matrix| )
    {
        discovered[it->first] = false;
        previous[it->first] = NULL;
    }
    discovered[start_node] = true;

    int node_count = adj.size();

    // Initialize layers
    list<string> layers[node_count];
    layers[0].push_back(start_node);

    // Layer counter
    int i = 0;



    string current = start_node;

    Edge *first_edge =NULL, *last_edge;

    bool search = true;
    while(search)
    {
        // If all layers are empyt, break
        if(layers[i].empty())
            break;

        current = layers[i].front();
        layers[i].pop_front();

        // Edge counter
        int j = 0;

        // For each edge
        for(edgeList_datatype::iterator it = adj[current].begin(); it != adj[current].end(); it++)
        {
            // If cannot push more flow from current, skip that edge
            if(it->flow == it->capacity)
            {
                j++;
                continue;
            }

            if( j == adj[current].size() )
            {
                search = false;
                break;
            }


            if(discovered[it->to] == false)
            {
                discovered[it->to] = true;
                layers[i+1].push_back(it->to);

                if(first_edge == NULL)
                    first_edge = &(*it);

                last_edge = &(*it);
                previous[it->to] = last_edge;
            }

            if(end_node.compare(it->to) == 0)
            {
                search = false;
                break;
            }
        }

        // Go to next layer if checked all
        if(layers[i].empty())
            i+= 1;
    }

    // Obtain the path
    stack<Edge *> temp_stack;
    Edge *current_edge = previous[end_node];

    // If no path found, return
    if(current_edge == NULL)
        return;

    while( current_edge->from.compare(start_node) != 0)
    {
        temp_stack.push(current_edge);
        current_edge = previous[current_edge->from];
    }
    temp_stack.push(first_edge);

    while(!temp_stack.empty())
    {
        path.push_back(temp_stack.top());
        temp_stack.pop();
    }
}


int Graph::augmentPath(AdjList &adj, vector<Edge *> &path, string &assignment_string)
{
    //NOTE: Bottleneck is given fixed in this problem
    int bottleneck = 1;

    int count=1;
    // For each edge in the path
    for(vector<Edge *>::const_iterator it = path.begin(); it != path.end(); it ++)
    {
        // Write object to robot assignments
        if(count++ == 2)
        {
            assignment_string += string((*it)->from);
            assignment_string += " to ";
            assignment_string += string((*it)->to);
            assignment_string += "\n";
        }

        (*it)->flow += bottleneck;
    }

    return bottleneck;
}


int Graph::fordFulkerson(string &assignment_string)
{
    string start = "s", end = "t";

    vector<Edge *> path;
    bfs(this->adj_list, start, end, path);

    int total_flow = 0;

    while(!path.empty())
    {
        total_flow += augmentPath(this->adj_list, path, assignment_string);

        path.clear();
        bfs(this->adj_list, start, end, path);
    }

    return total_flow;
}

void Graph::printValuesToScreen()
{

    for(AdjList::const_iterator it = adj_list.begin(); it!=adj_list.end(); it++)
    {
        cout << it->first;
        for(edgeList_datatype::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << "\t-> " << it2->to << " (" << it2->flow << "/" << it2->capacity << ")" << endl;
        }
        cout << endl;
    }
}

bool Graph::outputDotFile(string &filename)
{
    ofstream dot_output;
    dot_output.open(filename.c_str());
    if(!dot_output.is_open())
    {
        cout << "Graphviz output file:" << filename << " error!"  << endl;
        return false;
    }

    dot_output << "digraph G{" << endl;
    dot_output << "rankdir=\"LR\";" << endl;


    bool color_flows = true;
    string subgraph_robots("subgraph Objects{"), subgraph_objects("subgraph Robots{");

    for(AdjList::const_iterator it = adj_list.begin(); it!=adj_list.end(); it++)
    {
        for(edgeList_datatype::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            dot_output << it->first << "->" << it2->to;

            dot_output << " [";
            dot_output << " label=\" " << it2->flow << "/" << it2->capacity << "\"";
            if(color_flows && it2->flow != 0 && it2->flow < it2->capacity)
                dot_output << " color=\"blue\" ";
            else if(color_flows && it2->flow == it2->capacity)
                dot_output << " color=\"red\" ";
            dot_output << "];" << endl;
        }
    }

    dot_output << "}" << endl;
    return true;
}
