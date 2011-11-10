#include "date.h"
#include "kattistime.h"

#include <time.h>
#include <stdexcept>
#include <math.h>

#define EMPTY -1
#define DAY_IN_SECONDS 86400.0
#define DEBUG 0

namespace lab2 {

// Default constructor sets date to today
Date::Date() :
	cache( cache ), 
	julian_day_number((k_time(NULL) / DAY_IN_SECONDS) + 2440588) { clear_cache(); } //added 0.5

Date::Date(const Date& d) :
	cache( cache ),
	julian_day_number(d.julian_day_number) { clear_cache(); }

Date::Date(int jdn) :
	cache( cache ),
	julian_day_number(jdn) { clear_cache(); }

Date::~Date() {};

void Date::clear_cache() const {
	cache.year = EMPTY;
	cache.month = EMPTY;
	cache.day = EMPTY;
	cache.week_day = EMPTY;
}

std::ostream& operator<<(std::ostream & os, const Date& d) {
	os << d.year() << "-";
	if (d.month() < 10)
		os << "0"; 
	os << d.month() << "-";
	if (d.day() < 10)
		os << "0";
	os << d.day();
	if(DEBUG) {
		os << " <" << d.week_day_name() << ", "<< d.julian_day_number << " (jd) , " << d.mod_julian_day() << "(mod) > ";
	}
	return os;
}	
}