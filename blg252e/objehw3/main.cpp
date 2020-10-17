/*
* @Author
* Student Name: Cem Yusuf Aydoðdu
* Student ID : 150120251
* Date: 04.05.2015
*/

//
//  Notes: Operator += overload for Trip and
//  multiple trips does not work properly.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "trip.h"
#include "cruise.h"
#include "flight.h"

using namespace std;
int main() {

    Flight flight1("Istanbul-Ankara","TK213",212.5);
    Trip<Flight> flightTrip(flight1);

    try {
        flightTrip[0].setCost(186.5);

        // trying to get the element at(1)
        // should give an error
        cout << flightTrip[1] << endl;

    } catch (const string & err_msg) {

        cout << err_msg << endl;

    }

    cout<<flightTrip<<endl;

    Flight flight2("Ankara-Istanbul","TK312",203.5);
    flightTrip.add(flight2);

    cout<<flightTrip<<endl;

    Flight *flightArray= new Flight[2];

    flightArray[0]=  Flight("Istanbul-Izmir","TK113",183.5);

    flightArray[1]=  Flight("Izmir-Istanbul","TK311",162.5);

    Trip<Flight> flightTrip2(flightArray,2);

    delete [] flightArray;

//    flightTrip+=flightTrip2;

    try {

        flightTrip.setDiscount(10);

        // trying to set the discount to(50)
        // should give an error
        flightTrip.setDiscount(50);

    } catch (const string & err_msg) {

        cout << err_msg << endl;

    }

    cout<<flightTrip<<endl;

//    Trip<Trip<Flight> > multipleTrips;
//    multipleTrips.add(flightTrip);
//    multipleTrips.add(flightTrip2);
//    multipleTrips.setDiscount(20);
//
//    cout<<multipleTrips<<endl;

    Cruise c("Istanbul-Izmir",180.2);
    Trip<Cruise> crouseTrip(c);
    crouseTrip.setDiscount(15);

    cout<<crouseTrip<<endl;

}
