#include <time.h>
#include <math.h>

#include "WesternDate.h"
#include "Julian.h"

Julian::Julian() : WesternDate() {}
Julian::Julian(int year, int month, int day) {
	set_unix_timestamp(date2timestamp(year,month,day));
	cache.year = year;
	cache.month = month;
	cache.day = day;
}

bool Julian::is_leap_year(int year) const { return year % 4 == 0; } 

time_t Julian::date2timestamp(int year, int month, int day) {
	validate_date(year, month, day);
	return (time_t) (date2julianday(year,month,day) - 2440587.5)*DAYS_IN_SECS[0];
}
float Julian::date2julianday(int year, int month, int day) {
	if (month < 3) {
		month = month + 12;
		year = year - 1;
	}
	float julian_day = day + (153*month-457)/5 + 365*year + year/4 + 1721116.5;
	return julian_day;
}

void Julian::refresh_cache() const {
	float jd = julian_day();
	int z = (int) floor(jd - 1721116.5);
	float r = (jd - 1721116.5) - z;
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
	cache.week_day = (int(julian_day() + 1.5)) % 7; // <-- TODO FIX THIS
}