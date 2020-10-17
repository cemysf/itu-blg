#include<iostream>
#include "SystemManager.h"

int main() {
			
		SystemManager res;

		res.createAirport("DEN");
		res.createAirport("DFW");
		res.createAirport("LON");
		res.createAirport("DEN");//invalid
		res.createAirport("DENW");//invalid
				
		res.createAirline("DELTA");
		res.createAirline("AMER");
		res.createAirline("FRONT");
		res.createAirline("FRONTIER"); 
		res.createAirline("FRONT"); //invalid
		res.createAirline("DELTA"); //invalid

////Create flights
res.createFlight("DELTA", "DEN", "LON", 2015, 3, 17, "123");
res.createFlight("DELTA", "DEN", "DFW", 2009, 8, 8, "568K");
res.createFlight("FRONTIER", "LON", "DFW", 2010, 9, 8, "567");

//invalid
res.createFlight("JET", "LON", "DEN", 2009, 5, 7, "123");
res.createFlight("JET", "DEN", "LON", 2010, 6, 10, "786");
res.createFlight("JET", "DEN", "DenW", 2009, 1, 12, "909");
res.createFlight("AMER", "DEN", "LON", 2010, 10, 1, "123"); //flight id given before


//Create sections
//invalid
res.createSection("JET","123", 2, 2, 1);
res.createSection("JET","123", 1, 3, 2);
res.createSection("JET","123", 2, 3, 1);
res.createSection("SWSERTT","123", 5, 5, 1);
//valid
res.createSection("DELTA","123", 1, 1, 1);//business
res.createSection("DELTA","123", 1, 2, 1);//business
res.createSection("DELTA","123",1,3,3); //economy

res.findAvailableFlights("DEN", "LON");
res.bookSeat("DELTA", "123", 1, 1, 'A');
res.bookSeat("DELTA", "123", 3, 1, 'A');
res.bookSeat("DELTA", "123", 3, 1, 'B');
res.bookSeat("DELTA", "123", 1, 1, 'A'); //already booked
res.createSection("JET","123", 2, 2, 1); //invalid

res.displaySystemDetails();

	return 0;
	}

