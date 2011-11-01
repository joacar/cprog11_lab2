#ifndef _GREGORIAN_
#define _GREGORIAN_

#include <time.h>
#include "westerndate.h"

namespace lab2 
{

class Gregorian : public WesternDate {

private:
	bool is_leap_year(int year) const;

public:
	Gregorian();
	Gregorian(const Date& date);
	Gregorian(Date* dp);
	Gregorian(int year, int month, int day);

	time_t date2timestamp(int year, int month, int day);
	void refresh_cache() const;

};

}
#endif