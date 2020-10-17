/// BLG336E Analysis of Algorithms 2
/// Project 3
///
/// Cem Yusuf Aydoğdu
/// 150120251

#ifndef FLOWNETWORK_H
#define FLOWNETWORK_H

#include "graph.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <list>


using namespace std;

class FlowNetwork
{
    int object_count;
    int robot_count;

    Graph graph;

public:
    FlowNetwork();

    bool readFromFile(string &filename);

    void findAndWriteAssignment(string &filename);

    void printValuesToScreen();

    void outputAssignment(string &filename);

    void outputDotFile(string filename);
};

#endif // FLOWNETWORK_H
