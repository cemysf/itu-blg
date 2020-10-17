/// BLG336E Analysis of Algorithms 2
/// Project 3
///
/// Cem Yusuf Aydoğdu
/// 150120251
///
/// Compiling:
/// g++ *.cpp -o out
///
/// For compiling output dot files:
/// dot [filename] -Tpng -o [image.png]
///
#include "flownetwork.h"

int main()
{
    string input_fname = "input.txt";
    string output_fname = "output.txt";

    FlowNetwork flownetwork;

    if(flownetwork.readFromFile(input_fname))
    {
        // For visualization
        //flownetwork.outputDotFile(string("before_assignment.dot"));

        flownetwork.findAndWriteAssignment(output_fname);

        // For visualization
        //flownetwork.outputDotFile(string("after_assignment.dot"));
    }

    return 0;
}
