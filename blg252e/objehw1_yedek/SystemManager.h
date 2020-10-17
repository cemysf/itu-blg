#ifndef SYSTEMMANAGER_H_INCLUDED
#define SYSTEMMANAGER_H_INCLUDED

#include <string>
#include <iostream>

using namespace std;


class Seat
{
    unsigned short int rowNumber;
    char column;
    bool booked;
    Seat *next;

    public:

};


class FlightSection
{
    int seatClass;
    Seat *head;
    FlightSection *next;

    public:
};


class Airport
{
    string name;
    Airport *next;
    friend class SystemManager;

    public:
        Airport(const string &n){ name = n; next=NULL; }
};

class Flight
{
    string id;
    int yy, mm, dd;         //year,month,day

    Airport *origin_airport;
    Airport *dest_airport;

    FlightSection *head_section;
    Flight *next;
    friend class SystemManager;

    public:
        Flight(const string &flight_id,int year,int month,int day); //{ id = flight_id; head_section=NULL; next=NULL; }

};

Flight::Flight(const string &flight_id,int year,int month,int day )
{
    id = flight_id;
    yy = year;    mm = month;    dd = day;

    origin_airport=NULL;    dest_airport=NULL;

    head_section=NULL;  next=NULL;

}


class Airline
{
    string name;
    Flight *head_flight;
    Airline *next;
    friend class SystemManager;

    public:
        Airline(const string &n){ name = n; head_flight=NULL; next=NULL; }
};


class SystemManager
{
    Airport *head_airport;
    Airline *head_airline;

    public:
        SystemManager() { head_airline=NULL; head_airport=NULL; }

        bool createAirport(const string &n);
        bool createAirline(const string &n);
        bool createFlight(const string &aname,const string &orig, const string &dest,int year,int month,int day, const string &id);
        //(const string &aname, string orig, string dest,int year,int month,int day, string id);


        void displaySystemDetails();

};

bool SystemManager::createAirport(const string &n)
{
    if(n.size() != 3)
    {
        cerr << "ERROR:Airport name is wrong in size" << endl;
        return false;
    }


    Airport *new_airport, *traverse;

    if(head_airport)        //if list not empty
    {
        traverse = head_airport;
        while(traverse)
        {
            if(n.compare(traverse->name) == 0)
            {
                cerr << "ERROR:Airport '"<< n <<  "' already exists" << endl;
                return false;
            }

            else if(traverse->next == NULL)
                break;

            else traverse=traverse->next;
        }

        new_airport = new Airport(n);
        if(!new_airport)
        {
            cerr << "ERROR:Memory allocation failed" << endl;
            return false;
        }

        traverse->next = new_airport;
        new_airport->next = NULL;

    }
    else        // if list empty
    {
        new_airport = new Airport(n);
        if(!new_airport)
        {
            cerr << "ERROR:Memory allocation failed" << endl;
            return false;
        }

        head_airport = new_airport;
        head_airport->next = NULL;
    }

    return true;
}

bool SystemManager::createAirline(const string &n)
{
    Airline *new_airline, *traverse;

    if(head_airline)        //if list not empty
    {
        traverse = head_airline;
        while(traverse)
        {
            if( n.compare(traverse->name) == 0)
            {
                cerr << "ERROR:Airline '"<< n <<  "' already exists" << endl;
                return false;
            }

            else if(traverse->next == NULL)
                break;

            else traverse=traverse->next;
        }

        new_airline = new Airline(n);
        if(!new_airline)
        {
            cerr << "ERROR:Memory allocation failed" << endl;
            return false;
        }

        traverse->next = new_airline;
        new_airline->next = NULL;

    }
    else        // if list empty
    {
        new_airline = new Airline(n);
        if(!new_airline)
        {
            cerr << "ERROR:Memory allocation failed" << endl;
            return false;
        }

        head_airline = new_airline;
        head_airline->next = NULL;
    }

    return true;



}

bool SystemManager::createFlight(const string &aname,const string &orig, const string &dest,int year,int month,int day, const string &id)
{
    Airline *airline = head_airline;
    Airport *airport_orig = head_airport;
    Airport *airport_dest = head_airport;

    while(airline)
    {
        if(aname.compare(airline->name)==0)
            break;
        airline=airline->next;
    }

    if(airline==NULL)
    {
        cerr << "ERROR:(id="<< id <<")Airline not found" << endl;
        return false;
    }

    while(airport_orig)
    {
        if(orig.compare(airport_orig->name)==0)
            break;
        airport_orig=airport_orig->next;
    }

    if(airport_orig==NULL)
    {
        cerr << "ERROR:(id="<< id <<")Origin airport not found" << endl;
        return false;
    }

    while(airport_dest)
    {
        if(dest.compare(airport_dest->name)==0)
            break;
        airport_dest=airport_dest->next;
    }

    if(airport_dest==NULL)
    {
        cerr << "ERROR:(id="<< id <<")Destination airport not found" << endl;
        return false;
    }

    if(airport_dest->name.compare(airport_orig->name) == 0)
    {
        cerr << "ERROR:(id="<< id <<")Origin and destination are same" << endl;
        return false;
    }


    Flight *newFlight = new Flight(id,year,month,day);
    newFlight->origin_airport = airport_orig;
    newFlight->dest_airport = airport_dest;

    Flight *traverse = airline->head_flight;
    if(traverse)       //not the first flight of airline
    {
        while(traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = newFlight;
    }
    else
        airline->head_flight = newFlight;

    return true;

}

void SystemManager::displaySystemDetails()
{
    cout << "---Airports---" << endl;
    Airport *traverse_airports = head_airport;
    while(traverse_airports != NULL)
    {
        cout << traverse_airports->name << endl;
        traverse_airports=traverse_airports->next;
    }
    cout << endl;


    cout << "---Airlines---" << endl;
    Airline *traverse_airlines = head_airline;
    while(traverse_airlines != NULL)
    {
        cout << traverse_airlines->name << endl;
        if(traverse_airlines->head_flight != NULL)  //if this airline has flights
        {
            Flight *traverse_flights = traverse_airlines->head_flight;
            cout << string(5,' ') <<"--Flights--" << endl;

            cout << string(5,' ') <<"Orig" << "\t" << "Dest" << "\t" << "Year"<< "\t" << "Month" << "\t" << "Day"<< "\t" << "ID"<<endl;
            while(traverse_flights != NULL)
            {
                cout << string(5,' ') << traverse_flights->origin_airport->name << "\t" << traverse_flights->dest_airport->name << "\t"
                << traverse_flights->yy << "\t" << traverse_flights->mm << "\t" << traverse_flights->dd
                << "\t" << traverse_flights->id << endl;

                traverse_flights=traverse_flights->next;
            }

        }
        traverse_airlines=traverse_airlines->next;
        cout << endl;
    }
    cout << endl;

//    cout << "---   Airlines   ---" << endl;
//    traverse_airlines = head_airline;
//    Flight *traverse_flights = traverse_airlines->head_flight;
//    while(traverse_flights != NULL && traverse_airlines !=NULL)
//    {
//        cout << traverse_airlines->name << endl;
//        traverse_airlines=traverse_airlines->next;
//    }
//    cout << endl;



}




#endif // SYSTEMMANAGER_H_INCLUDED