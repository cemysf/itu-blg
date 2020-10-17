/*
* @Author
* Student Name: Cem Yusuf Aydoðdu
* Student ID : 150120251
* Date: 04.05.2015
*/

#ifndef FLIGHT_H_INCLUDED
#define FLIGHT_H_INCLUDED
#include "trip.h"

using namespace std;

class Flight : public Carrier{
    string flightID;

    public:
        Flight():Carrier() { }
        Flight(string source_dest, string ID, float flightCost) : Carrier(source_dest,flightCost) { flightID = ID; }

        string getID() { return flightID; }
        void setID(string newID) { flightID = newID; }

        void print() { cout << "Flight Name: "<< path << " " << flightID << " Cost : " << cost << endl; }

        friend ostream& operator<<(ostream &out, Flight &t)
        {
            out << "Flight Name: "<< t.path << " " << t.flightID << " Cost : " << t.cost << endl;
            return out;

        }
};


#endif // FLIGHT_H_INCLUDED
