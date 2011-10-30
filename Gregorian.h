#ifndef _GREGORIAN_
#define _GREGORIAN_

#include <time.h>
#include "WesternDate.h"

class Gregorian : public WesternDate {

private:
	bool is_leap_year(int year);

public:
	Gregorian();
	Gregorian(int year, int month, int day);

	time_t date2timestamp(int year, int month, int day);
	void refresh_cache();

};

#endif