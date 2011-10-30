#include <iostream>

#include "Gregorian.h"
#include "Julian.h"

int main(){
	// Set kattistime to right now
	// time_t time_now;
	// time(&time_now);
	// set_k_time(time_now);

	Gregorian gtoday;
	std::cout << "Gregorian: " << gtoday << std::endl;
	Julian jtoday;
	std::cout << "Julian: " << jtoday << std::endl;

	std::cout << "Gregorian(2012,2,29) - 1 year + 1 year" << std::endl;	
	Gregorian gleap = Gregorian(2012,2,29);
	gleap.add_year(-1).add_year(1);
	std::cout << gleap << std::endl;
	std::cout << "Gregorian(2011,12,16) - 276 months" << std::endl;	
	Gregorian gleap2 = Gregorian(2011,12,16);
	gleap2.add_month(-276);
	std::cout << gleap2 << std::endl;
	
	return 0;
}