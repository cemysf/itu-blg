//
//  BLG252E HW1
//
//  Cem Yusuf Aydoğdu
//  150120251
//
//
//  Notes:
//  Program only shows error messages, there is no confirmation message about an action
//  Different types of error messages begin with different number of spaces, for easy reading
//  All airport and airline names are hold in upper characters
//  While creating flight, past dates cannot be used
//
//

#include <string>
#include <iostream>
#include "SystemManager.h"
using namespace std;

int main()
{
    SystemManager res;

    res.createAirport("DEN");
    res.createAirport("dfw");
    res.createAirport("LON");
    res.createAirport("DEN");//invalid, same name created before
    res.createAirport("denw");//invalid more than 3 chars

    res.createAirline("DELTA");
    res.createAirline("AMER");
    res.createAirline("FRONT");

    res.createAirline("front"); //invalid same name created before

    res.createFlight("DELTA", "DEN", "LON", 2015, 6, 28, "123");
    res.createFlight("DELTA", "DEN", "DEH", 2015, 8, 8, "567abc");//invalid airport
    res.createFlight("DEL", "DEN", "LON", 2015, 9, 8, "567"); //invalid airline
    res.createFlight("DELTA", "LON33", "DEN33", 2015, 5, 7, "123");//invalid airports
    res.createFlight("AMER", "DEN", "LON", 2015, 40, 100, "123abc");//invalid date

    res.createSection("DELTA","123", 2, 2, 3);
    res.createSection("DELTA","123", 2, 3, 1);
    res.createSection("DELTA","123", 2, 3, 1);//Invalid
    res.createSection("SWSERTT","123", 5, 5, 3);//Invalid airline

    res.bookSeat("DELTA", "123", 1, 1, 'A');
    res.bookSeat("DELTA", "123", 3, 1, 'A');
    res.bookSeat("DELTA", "123", 3, 1, 'B');
    res.bookSeat("DELTA888", "123", 2, 1, 'A'); //Invalid airline
    res.bookSeat("DELTA", "123haha7", 2, 1, 'A'); //Invalid flightId
    res.bookSeat("DELTA", "123", 3, 1, 'A'); //already booked

    res.displaySystemDetails();
    res.findAvailableFlights("DEN", "LON");

    return 0;
}
