#include <time.h>
#include "WesternDate.h"
#include "Gregorian.h"

namespace lab2 {

bool Gregorian::is_leap_year(int year) const
{
	return (year % 100 == 0 && year % 400 == 0) || (year % 4 == 0);
}

Gregorian::Gregorian() : WesternDate() {}	
Gregorian::Gregorian(const Date& rhs) : WesternDate(rhs) {}
Gregorian::Gregorian(Date* dp) : WesternDate(dp) {}
Gregorian::Gregorian(int year, int month, int day) {
	set_unix_timestamp(date2timestamp(year,month,day));
	cache.year = year;
	cache.month = month;
	cache.day = day;
}

time_t Gregorian::date2timestamp(int year, int month, int day)
{
	validate_date(year, month, day);

	time_t rawtime = 0;
	struct tm* given_date = localtime(&rawtime);
	given_date->tm_year = year - 1900;
	given_date->tm_mon = month - 1;
	given_date->tm_mday = day;
	return mktime(given_date);	
}

void Gregorian::refresh_cache() const
{
	time_t timestamp = get_unix_timestamp();
	const struct tm* t = localtime(&timestamp);
	cache.year = t->tm_year + 1900;
	cache.month = t->tm_mon + 1;
	cache.day = t->tm_mday;
	cache.week_day = t->tm_wday;
}

}