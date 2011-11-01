#include "westerndate.h"
#include "gregorian.h"

namespace lab2 {

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

float Gregorian::date2julian_day_number(int year, int month, int day)
{
	validate_date(year,month,day);
	return 2455867;	
}

void Gregorian::refresh_cache() const
{
	float julian_day_number = get_julian_day_number();
	cache.year = 2011;
	cache.month = 11;
	cache.day = 1;
	cache.week_day = 2;
}

}