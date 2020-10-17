/// BLG336E Analysis of Algorithms 2
/// Project 3
///
/// Cem Yusuf Aydoğdu
/// 150120251

#include "flownetwork.h"

FlowNetwork::FlowNetwork()
{

}

bool FlowNetwork::readFromFile(string &filename)
{
    ifstream file(filename.c_str(), ios::in);
    if(!file.is_open())
    {
        cout << "File error: cannot open " << filename << endl;
        return false;
    }

    string line;
    int temp;

    // Parse first line, get object and robot count
    getline(file, line);
    {
        stringstream ss(line);
        ss >> object_count;
        ss >> robot_count;
    }

    // Add edges from s to objects
    string source_node = "s";
    edgeList_datatype edge_list;
    for(int i=0; i<object_count; i++)
    {
        ostringstream oss;
        oss << "Obj" << i+1;

        Edge e = {source_node, oss.str(), 0, 1};

        edge_list.push_back(e);
    }
    graph.addNewNode(source_node, edge_list);


    // Parse lines to obtain directed edges from objects to robots ( i.e connect each object to their compatible robots)
    for(int i=0; i<object_count; i++)
    {
        getline(file, line);

        // Construct name of current object
        ostringstream oss;
        oss << "Obj" << i+1;
        string obj_name = oss.str();

        edgeList_datatype edge_list;

        stringstream ss(line);
        for(int j=0; j<robot_count; j++)
        {
            ss >> temp;
            if(temp == 1)
            {
                // Construct name of robot which is pointed by current object
                ostringstream oss;
                oss << "Rob" << j+1;
                string robot_name = oss.str();

                Edge e = {obj_name, robot_name, 0, 1};
                edge_list.push_back(e);
            }
        }


        graph.addNewNode(obj_name, edge_list);
    }

    // From robots to sink (t), capacities are read from last line of the file
    getline(file,line);
    stringstream ss(line);
    for(int i=0; i<robot_count; i++)
    {
        ss >> temp;

        ostringstream oss;
        oss << "Rob" << i+1;
        string robot_name = oss.str();

        Edge edge = {robot_name, string("t"), 0, temp};

        graph.addNewNode(robot_name);
        graph.addEdgeToNode(robot_name, edge);
    }

    return true;
}

void FlowNetwork::findAndWriteAssignment(string &filename)
{
    string out_assignment;
    int result = graph.fordFulkerson(out_assignment);
    if(result == object_count)
    {
        out_assignment = "Assignment below is feasible\n\n" + out_assignment;
    }
    else
    {
        out_assignment = "No feasible allocation exists, cannot map all objects to robots\n\n" + out_assignment;
    }
    cout << out_assignment;

    ofstream file;
    file.open(filename.c_str());
    cout << endl;
    if(!file.is_open())
    {
        cout << "ERROR: Cannot output to " << filename << endl;
        return;
    }
    file << out_assignment;
    cout << "Output saved to " << filename << endl;
    cout << endl;
}


void FlowNetwork::printValuesToScreen()
{
    cout << "object_count" << "\t:\t" << object_count << endl;
    cout << "robot_count" << "\t:\t" << robot_count << endl;

    cout << "adj_matrix" << endl;
    graph.printValuesToScreen();

}

void FlowNetwork::outputDotFile(string filename)
{
    if(graph.outputDotFile(filename))
        cout << "Dot file saved to " << filename << endl;
    else
        cout << "ERROR: Cannot save dot file to " << filename << endl;
    cout << endl;
}
