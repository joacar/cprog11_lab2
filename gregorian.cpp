#include "gregorian.h"

#include <math.h>
#include <stdexcept>

namespace lab2 {

Gregorian::Gregorian() : WesternDate() {}	
Gregorian::Gregorian(const Date& d) : WesternDate(d) {}
Gregorian::Gregorian(int year, int month, int day) {
	date2julian_day_number(year, month, day);

	if(!validate_date(year, month, day)) {
		throw std::out_of_range("Invalid range");
	}

	// TODO better way to set below?
	cache.year = year;
	cache.month = month;
	cache.day = day;
	//cache.week_day = week_day();
}

// http://robm.fastmail.fm/articles/date_class.html
void Gregorian::date2julian_day_number(int year, int month, int day) {
	float a = (14-month)/12;
	float y = year+4800-a;
	float m = month + 12*a - 3;

	julian_day_number =	day + (153*m+2)/5 + y*365 + int( y/4 ) - int( y/100 ) + int( y/400 ) - 32045;	
}

// http://robm.fastmail.fm/articles/date_class.html
void Gregorian::refresh_cache() const {
	// http://en.wikipedia.org/wiki/Julian_day#Gregorian_calendar_from_Julian_day_number
	int jdn = julian_day_number; //floor( julian_day_number + 0.5 );
	int j = jdn + 32044;
	int g = j/146097;
	int dg = j % 146097;
	int c = (dg/36524 + 1) * 3/4 ;
	int dc = dg - c * 36524;
	int b = dc / 1461;
	int db = dc % 1461;
	int a = (db / 365 + 1) * 3 / 4;
	int da = db - a * 365;
	int y = g * 400 + c * 100 + b * 4 + a;
	int m = (da * 5 + 308) / 153 - 2;
	int d = da - (m + 4) * 153 / 5 + 122;

	cache.day 		= d + 1;
	cache.month 	= (m + 2) % 12 + 1; 
	cache.year 		= y - 4800 + (m + 2) / 12;
	cache.week_day 	= (jdn % 7) + 1;
}

// http://en.wikipedia.org/wiki/Leap_year#Algorithm
bool Gregorian::is_leap_year(int year) const {
	if(year % 400 == 0) return true;
	if(year % 100 == 0) return false;
	if(year % 4 == 0) return true;
	return false;
}

}