#include <iostream>

#include "Gregorian.h"
#include "Julian.h"

using namespace lab2;

int main(){
	// Set kattistime to right now
	// time_t time_now;
	// time(&time_now);
	// set_k_time(time_now);

	Gregorian gtoday;
	std::cout << "Gregorian: " << gtoday << std::endl;
	Julian jtoday;
	std::cout << "Julian: " << jtoday << std::endl;

	std::cout << "Today it is " << gtoday << " gregorian and " << jtoday << " julian";
	if (gtoday - jtoday == 0) std::cout << ". It is the same date" << std::endl;
	if (gtoday - jtoday == 0) std::cout << "It is still the same date" << std::endl;

	std::cout << "\n**Add one day**\n";
	++gtoday; ++jtoday;
	std::cout << "It is " << gtoday << " gregorian and " << jtoday << " julian" << std::endl;
	if (gtoday - jtoday == 0) std::cout << "It is the same date\n" << std::endl;
	
	std::cout << "\n**Add yet another day**\n";
	++gtoday; ++jtoday;
	std::cout << "It is " << gtoday << " gregorian and " << jtoday << " julian" << std::endl;
	if (gtoday - jtoday == 0) std::cout << "It is the same date\n" << std::endl;
		

	std::cout << "\n**Add one month**\n";
	gtoday.add_month(1); jtoday.add_month(1);
	std::cout << "It is " << gtoday << " gregorian and " << jtoday << " julian" << std::endl;
	if (gtoday - jtoday == 0) {
		std::cout << "It is the same date\n" << std::endl;
	} 
	else {
		std::cout << "It is _NOT_ the same date\n" << std::endl;	
	} 

	std::cout << "Gregorian(2012,2,29), do add_year(-1) followed by add_year(+1)" << std::endl;	
	Gregorian gleap = Gregorian(2012,2,29);
	gleap.add_year(-1).add_year(1);
	std::cout << gleap << std::endl;
	std::cout << "Gregorian(2011,12,16) - 276 months" << std::endl;	
	Gregorian gleap2 = Gregorian(2011,12,16);
	gleap2.add_month(-276);
	std::cout << gleap2 << std::endl;


	
	return 0;
}