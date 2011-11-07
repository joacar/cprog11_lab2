#include <time.h>
#include <math.h>

#include "westerndate.h"
#include "julian.h"
#include "date_conversions.h"

namespace lab2 {

Julian::Julian() : WesternDate() {}
Julian::Julian(const Date& rhs) : WesternDate(rhs) {}
Julian::Julian(Date* dp) : WesternDate(dp) {}
Julian::Julian(int year, int month, int day) {
	set_julian_day_number(date2julian_day_number(year,month,day));
	cache.year = year;
	cache.month = month;
	cache.day = day;
}

bool Julian::is_leap_year(int year) const { return year % 4 == 0; } 

double Julian::date2julian_day_number(int year, int month, int day) {
	validate_date(year, month, day);
	// if (month < 3) {
	// 	month = month + 12;
	// 	year = year - 1;
	// }

	// double julian_day = day + (int)((153*month-457)/5.0) + 365.25*year + 1721116.5;
	// return julian_day;
	return DateConversions::ymd_to_jdn(year,month,day,1);
}

void Julian::refresh_cache() const {
	double jdn = get_julian_day_number();
	// int z = (int) floor(jd - 1721116.5);
	// double r = (jd - 1721116.5) - z;
	// int y = (int) floor((z-0.25)/365.25);
	// int c = (int) (z - floor(365.25*y));
	// int m = (5*c + 456)/153;
	// int f = (153*m-457)/5;

	// cache.day = c - f + r;
	// if (m > 12) {
	// 	y = y + 1;
	// 	m = m - 12;
	// }
	// cache.year = y;
	// cache.month = m;
	cache.week_day = int(jdn + 1.5) % 7;
	DateConversions::jdn_to_ymd(jdn, &cache.year, &cache.month, &cache.day, 1);
}

}