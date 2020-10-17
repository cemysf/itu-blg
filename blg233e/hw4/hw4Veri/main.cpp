#include <iostream>
#include "datastr.h"

using namespace std;
typedef str stacks;

int main()
{
    stacks records;
    records.initLists();
    if(!records.readFromFile()) return (-1);
    records.arrange();

    cout << "Arranged list: " << endl;
    records.print(records.head_tempstack);

    if(!records.writeToFile()) return (-1);
    else cout << endl <<  "Writed succesfully.." << endl;

    records.closeLists();
    return 0;
}
