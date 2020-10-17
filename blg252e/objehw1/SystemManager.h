//
//  BLG252E HW1
//
//  Cem Yusuf Aydoğdu
//  150120251
//
//  Notes:
//
//  Linked list structures are represented by  "L---->"
//  Flights also connected to associated airports, flightSection contains 2D array
//
//  SystemManager--->Airport
//      |
//      L----------->Airline
//                      |
//                      L----->Flight
//                                |
//                                L----->FlightSection
//                                          |
//                                        *seatArray
//
//
#ifndef SYSTEMMANAGER_H_INCLUDED
#define SYSTEMMANAGER_H_INCLUDED

#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Seat
{
    int rowNumber;
    char column;
    bool booked;
    friend class FlightSection;
    friend class SystemManager;
};


class FlightSection
{
    const int rows,cols,seatClass;
    Seat *seatArray;
    FlightSection *next;

    friend class SystemManager;
    friend class Flight;
    public:
        FlightSection(int r, int c, int s);
        ~FlightSection() {delete [] seatArray;}
};

FlightSection::FlightSection(int r, int c, int s) : rows(r), cols(c), seatClass(s)
{
    next=NULL;
    seatArray = new Seat[rows * cols];

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            seatArray[i*rows + j].rowNumber = i+1;
            seatArray[i*rows + j].column = 'A' + j; // j+1;
            seatArray[i*rows + j].booked = false;
        }
    }
}

class Airport
{
    const string name;
    Airport *next;
    friend class SystemManager;

    public:
        Airport(const string &n): name(n){ next=NULL; }
};

class Flight
{
    const string id;
    const int yy, mm, dd;         //year,month,day

    Airport *origin_airport;
    Airport *dest_airport;

    FlightSection *head_section;
    Flight *next;
    friend class SystemManager;
    friend class Airline;
    public:
        Flight(const string &flight_id,int year,int month,int day);
        ~Flight();

};

Flight::Flight(const string &flight_id,int year,int month,int day ): id(flight_id), yy(year), mm(month), dd(day)
{
    origin_airport=NULL;
    dest_airport=NULL;
    head_section=NULL;  next=NULL;
}

Flight::~Flight()
{
    FlightSection *temp;
    while(head_section)
    {
        temp = head_section;
        head_section=head_section->next;
        delete temp;
    }
}


class Airline
{
    const string name;
    Flight *head_flight;
    Airline *next;
    friend class SystemManager;

    public:
        Airline(const string &n): name(n){ head_flight=NULL; next=NULL; }
        ~Airline();
};

Airline::~Airline()
{
    Flight *temp;
    while(head_flight)
    {
        temp = head_flight;
        head_flight=head_flight->next;
        delete temp;
    }
}


class SystemManager
{
    Airport *head_airport;
    Airline *head_airline;

    public:
        SystemManager() { head_airline=NULL; head_airport=NULL; }
        bool createAirport(const string &n);
        bool createAirline(const string &n);
        bool createFlight(const string &aname,const string &orig, const string &dest,int year,int month,int day, const string &id);
        bool createSection(const string &air,const string &flID, int rows, int cols, int s);
        bool findAvailableFlights(const string &orig, const string &dest);
        bool bookSeat(const string &airln, const string &flight, int section, int row, const char &col);
        void printSeats(int r, int c, Seat *array_adr);
        void displaySystemDetails();
};

bool SystemManager::createAirport(const string &n)
{
    if(n.size() != 3)
    {
        cerr << "ERROR:Airport name is wrong in size" << endl;
        return false;
    }

    string n_upper;
    for(int c=0; c < n.size(); c++)
        n_upper += ( (char)(toupper(n[c])) );

    Airport *new_airport, *traverse;

    if(head_airport)        //if list not empty
    {
        traverse = head_airport;
        while(traverse)
        {
            if(n_upper.compare(traverse->name) == 0)
            {
                cerr << "ERROR:Airport '"<< n <<  "' already exists" << endl;
                return false;
            }

            else if(traverse->next == NULL)
                break;

            else traverse=traverse->next;
        }

        new_airport = new Airport(n_upper);
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

    string n_upper;
    for(char c=0; c < n.size(); c++)
        n_upper += ( (char)(toupper(n[c])) );

    if(head_airline)        //if list not empty
    {
        traverse = head_airline;
        while(traverse)
        {
            if( n_upper.compare(traverse->name) == 0)
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
        new_airline = new Airline(n_upper);
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
    time_t t = time(0);
    struct tm *currTime = localtime(&t);

    //checking date
    if((year < (currTime->tm_year + 1900)) ||
    ((year == currTime->tm_year + 1900) && (month < (currTime->tm_mon + 1))) ||
    ((year == currTime->tm_year + 1900) && (month == (currTime->tm_mon + 1)) && (day < currTime->tm_mday)) ||
    (month > 12 || day > 31))
    {
        cerr << " ERROR while creating flight:(id="<< id <<") Invalid or passed date" << endl;
        return false;
    }

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
        cerr << " ERROR while creating flight:(id="<< id <<") Airline not found" << endl;
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
        cerr << " ERROR while creating flight:(id="<< id <<") Origin airport not found" << endl;
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
        cerr << " ERROR while creating flight:(id="<< id <<") Destination airport not found" << endl;
        return false;
    }

    if(airport_dest->name.compare(airport_orig->name) == 0)
    {
        cerr << " ERROR while creating flight:(id="<< id <<") Origin and destination are same" << endl;
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

bool SystemManager::createSection(const string &air,const string &flID, int rows, int cols, int s)
{
    Airline *airline = head_airline;

    while(airline)
    {
        if(air.compare(airline->name)==0)
            break;
        airline=airline->next;
    }

    if(airline==NULL)
    {
        cerr << "  ERROR while creating section:(flID="<< flID <<")Airline not found" << endl;
        return false;
    }

    Flight *flight = airline->head_flight;

    while(flight)
    {
        if(flID.compare(flight->id)==0)
            break;
        flight=flight->next;
    }

    if(flight==NULL)
    {
        cerr << "  ERROR while creating section:(flID="<< flID <<")Flight not found" << endl;
        return false;
    }

    FlightSection *traverse = flight->head_section;

    while(traverse)
    {
        if(traverse->seatClass == s)
        {
            cerr << "  ERROR while creating section:(flID="<< flID <<")Section already exists" << endl;
            return false;
        }
        traverse=traverse->next;
    }

    traverse =  flight->head_section;
    FlightSection *newSect = new FlightSection(rows,cols,s);
    if(traverse)
    {
        while(traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = newSect;
    }
    else
        flight->head_section = newSect;

    return true;
}

bool SystemManager::findAvailableFlights(const string &orig, const string &dest)
{
    if(orig.compare(dest) == 0)
    {
        cerr << " ERROR while finding flights: Origin and destination are same" << endl;
        return false;
    }

    cout << "------- Available Flights -------" << endl;
    cout  << "Orig" << "\t" << "Dest" << "\t" << "Airline" << "\t" << "Year"<< "\t" << "Month" << "\t" << "Day"<< "\t" << "ID"<<endl;
    Airline *traverse_airline=head_airline;
    Flight *traverse_flights;

    while(traverse_airline)
    {
        traverse_flights = traverse_airline->head_flight;
        while(traverse_flights)
        {
            if(orig.compare(traverse_flights->origin_airport->name)== 0 && dest.compare(traverse_flights->dest_airport->name)==0)
                cout << traverse_flights->origin_airport->name << "\t" << traverse_flights->dest_airport->name << "\t"
                << traverse_airline->name << "\t" << traverse_flights->yy << "\t" << traverse_flights->mm << "\t" << traverse_flights->dd
                << "\t" << traverse_flights->id << endl;
            traverse_flights = traverse_flights->next;

        }
        traverse_airline = traverse_airline->next;


    }

    return true;
}

bool SystemManager::bookSeat(const string &airln, const string &flight, int section, int row, const char &col)
{
    Airline *traverse_airline = head_airline;
    while(traverse_airline)
    {
        if(airln.compare(traverse_airline->name)==0)
            break;
        traverse_airline = traverse_airline->next;
    }
    if(traverse_airline==NULL)
    {
        cerr << "   ERROR while booking seat: Airline not found" << endl;
        return false;
    }

    Flight *traverse_flights = traverse_airline->head_flight;
    while(traverse_flights)
    {
        if(flight.compare(traverse_flights->id)==0)
            break;
        traverse_flights = traverse_flights->next;
    }
    if(traverse_flights==NULL)
    {
        cerr << "   ERROR while booking seat: Flight not found" << endl;
        return false;
    }

    FlightSection *traverse_sect = traverse_flights->head_section;
    while(traverse_sect)
    {
        if(section == traverse_sect->seatClass)
            break;
        traverse_sect = traverse_sect->next;
    }
    if(traverse_sect==NULL)
    {
        cerr << "   ERROR while booking seat: Section not found" << endl;
        return false;
    }

    int colNumber = col - 'A';
    if(row > traverse_sect->rows || colNumber > traverse_sect->cols)
    {
        cerr << "   ERROR while booking seat: Row or column is not found" << endl;
        return false;
    }

    if(traverse_sect->seatArray[row*(traverse_sect->rows) + colNumber].booked == false)
    {
        //cout << "Seat booked: Row:" << row << "Column:" << col << endl;
        traverse_sect->seatArray[row*(traverse_sect->rows) + colNumber].booked = true;
    }
    else
    {
        cerr << "   ERROR while booking seat: Seat already booked" << endl;
    }
    return true;
}

void SystemManager::printSeats(int r, int c, Seat *array_adr)
{
    int i,j;
    cout << string(12,' ');
    for(i=0; i<c; i++)
        cout << char(65 + i) << " " ;
    cout << endl;

    for(i=0; i < r; i++)
    {
        cout << string(10,' ') << i+1 << " ";
        for(j=0; j < c; j++)
        {
            if(! array_adr[i*r + j].booked) cout << "0 ";
            else cout << "1 ";
        }
        cout << endl;
    }
}

void SystemManager::displaySystemDetails()
{
    cout << "------- System Details -------" << endl;
    cout << "---Airports---" << endl;
    Airport *traverse_airports = head_airport;
    while(traverse_airports != NULL)
    {
        cout << traverse_airports->name << endl;
        traverse_airports=traverse_airports->next;
    }
    cout << endl;

    Airline *traverse_airlines = head_airline;
    cout << "---Airlines---" << endl;
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

                cout << string(9,' ') <<"--Sections--" << endl;
                cout << string(9,' ') <<"Class" << "\t\t" << "Rows" << "\t" << "Columns"<< endl;
                FlightSection *traverse_flSect = traverse_flights->head_section;
                while(traverse_flSect != NULL)
                {
                    string s_class;
                    switch(traverse_flSect->seatClass)
                    {
                        case 1: s_class="Business";
                            break;
                        case 2: s_class="First\t";
                            break;
                        case 3: s_class="Economy";
                            break;
                    }

                    cout << string(9,' ') << s_class << "\t"
                    << traverse_flSect->rows << "\t" << traverse_flSect->cols << endl;

                    ///
                    printSeats(traverse_flSect->rows, traverse_flSect->cols, traverse_flSect->seatArray);
                    traverse_flSect = traverse_flSect->next;
                }
                traverse_flights=traverse_flights->next;
                cout << endl;
            }
        }
        traverse_airlines=traverse_airlines->next;
        cout << endl;
    }
}

#endif // SYSTEMMANAGER_H_INCLUDED