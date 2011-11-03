#include "westerndate.h"
#include "gregorian.h"

namespace lab2 {

// http://en.wikipedia.org/wiki/Leap_year#Algorithm
bool Gregorian::is_leap_year(int year) const
{
	return (year % 100 == 0 && year % 400 == 0) || (year % 4 == 0);
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
float Gregorian::date2julian_day_number(int year, int month, int day)
{
	validate_date(year,month,day);

	float a = (14-month)/12;
	float y = year+4800-a;
	float m = month + 12*a - 3;

	return day + (153*m+2)/5 + y*365 + y/4 - y/100 + y/400 - 32045;	
}

// http://robm.fastmail.fm/articles/date_class.html
void Gregorian::refresh_cache() const
{
	float jd = get_julian_day_number();
	float a = jd + 32044;
	float b = (4*a+3)/146097;
	float c = a - (b*146097)/4;

	float d = (4*c+3)/1461;
	float e = c - (1461*d)/4;
	float m = (5*e+2)/153;

	cache.day = (int)(e - (153*m+2)/5 + 1);
	cache.month = (int)(m + 3 - 12*(m/10));
	cache.year = (int)(b*100 + d - 4800 + m/10);
	cache.week_day = int(jd) % 7 + 1;
}

}