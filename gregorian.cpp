#include <math.h>	// really?!?!

#include "westerndate.h"
#include "gregorian.h"

namespace lab2 {

// http://en.wikipedia.org/wiki/Leap_year#Algorithm
bool Gregorian::is_leap_year(int year) const
{
	return (year % 4 == 0 && year % 100 == 0 && year % 400 == 0);
}

Gregorian::Gregorian() : WesternDate() {}	
Gregorian::Gregorian(const Date& rhs) : WesternDate(rhs) {}
Gregorian::Gregorian(Date* dp) : WesternDate(dp) {}
Gregorian::Gregorian(int year, int month, int day) {
	set_julian_day_number(date2julian_day_number(year,month,day));
	cache.year = year;
	cache.month = month;
	cache.day = day;
}

// http://robm.fastmail.fm/articles/date_class.html
double Gregorian::date2julian_day_number(int year, int month, int day)
{
	validate_date(year,month,day);

	double a = (14-month)/12;
	double y = year+4800-a;
	double m = month + 12*a - 3;

	return day + int( (153*m+2)/5.0 ) + int( y*365 ) + int( y/4.0 ) - int( y/100.0 ) + int( y/400.0 ) - 32045;	
}

// http://robm.fastmail.fm/articles/date_class.html
void Gregorian::refresh_cache() const
{
	/*double jd = get_julian_day_number();
	double a = jd + 32044;
	double b = (4*a+3)/146097;
	double c = a - (b*146097)/4;

	double d = (4*c+3)/1461;
	double e = c - (1461*d)/4;
	double m = (5*e+2)/153;

	cache.day = (int)(e - (153*m+2)/5 + 1);
	cache.month = (int)(m + 3 - 12*(m/10));
	cache.year = (int)(b*100 + d - 4800 + m/10);
	cache.week_day = int(jd) % 7 + 1;*/

	// http://en.wikipedia.org/wiki/Julian_day#Gregorian_calendar_from_Julian_day_number
	int jdn = floor( get_julian_day_number() + 0.5 );
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
	cache.week_day 	= (jdn % 7);
}

}