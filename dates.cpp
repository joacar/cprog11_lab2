#include <iostream>
#include <time.h>

#include "gregorian.h"
#include "julian.h"
#include "kattistime.h"

using namespace lab2;

int main(){
	// Set kattistime to right now
	time_t time_now;
	time(&time_now);
	set_k_time(time_now);

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

	Gregorian first = Gregorian(1858,1,1);
	std::cout << first << " " << first.week_day_name() << " " << first.mod_julian_day() << std::endl;
	Gregorian last = Gregorian(2558,12,31);
	std::cout << last <<  " " << last.week_day_name() << " " << last.mod_julian_day() << std::endl;
	
	return 0;
}