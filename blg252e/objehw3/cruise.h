/*
* @Author
* Student Name: Cem Yusuf Aydoğdu
* Student ID : 150120251
* Date: 04.05.2015
*/

#ifndef CRUISE_H_INCLUDED
#define CRUISE_H_INCLUDED
#include "trip.h"

class Cruise : public Carrier{

    public:
        Cruise(string source_dest, float cruiseCost) : Carrier(source_dest,cruiseCost) {}
        void print() { cout << "Cruise Name: "<< path << " Cost : " << cost << endl; }

        friend ostream& operator<<(ostream &out, Cruise &t)
        {
            out << "Cruise Name: "<< t.path << " Cost : " << t.cost << endl;
            return out;
        }
};

#endif // CRUISE_H_INCLUDED
