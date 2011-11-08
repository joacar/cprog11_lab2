#include "julian.h"

#include <time.h>
#include <math.h>
#include <stdexcept>

namespace lab2 {

Julian::Julian() : WesternDate() {}
Julian::Julian(const Date& d) : WesternDate(d) {}
Julian::Julian(int year, int month, int day) {
	date2julian_day_number(year,month,day);
	
	if(!validate_date(year, month, day)) {
		throw std::out_of_range("Invalid range");
	}

	// TODO better way to set below?
	cache.year = year;
	cache.month = month;
	cache.day = day;
	//cache.week_day = week_day();
}

void Julian::date2julian_day_number(int year, int month, int day) {
	
	if (month < 3) {
		month = month + 12;
		year = year - 1;
	}
	julian_day_number = day + (153*month-457)/5 + 365*year + (int)year/4 + 1721117; // added 0.5
}

void Julian::refresh_cache() const {

	if(cache.year != -1 && cache.month != -1 && cache.day != -1) 
		return;
	
	float jdn = julian_day_number;
	int z = (int) floor(jdn - 1721116.5);
	float r = (jdn - 1721116.5) - z;
	int y = (int) floor((z-0.25)/365.25);
	int c = (int) (z - floor(365.25*y));
	int m = (5*c + 456)/153;
	int f = (153*m-457)/5;

	cache.day = c - f + r;
	if (m > 12) {
		y = y + 1;
		m = m - 12;
	}
	cache.year = y;
	cache.month = m;
	cache.week_day = int((jdn + 1.5)) % 7;
}

}