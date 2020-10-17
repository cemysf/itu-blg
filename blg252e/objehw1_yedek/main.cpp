///
///     BLG252E HW1
///
///     Cem Yusuf Aydoðdu
///     150120251
///

#include <string>
#include <iostream>
#include "SystemManager.h"
using namespace std;

int main()
{
    SystemManager sys;

    sys.createAirport("asd");
    sys.createAirport("sdf");
    sys.createAirport("qwe");
    sys.createAirport("qwe");

    sys.createAirline("line1");
    sys.createAirline("LINE1");

    sys.createFlight("line1","asd","sdf",2015,10,3,"idA123sa");



    sys.displaySystemDetails();

    return 0;
}
