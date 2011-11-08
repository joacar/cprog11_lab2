#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "westerndate.h"

namespace lab2 
{

class Gregorian : public WesternDate {

public:
	Gregorian();
	Gregorian(const Date& date);
	Gregorian(Date* dp);
	Gregorian(int year, int month, int day);

	bool is_leap_year(int year) const;
	double date2julian_day_number(int year, int month, int day);
	void refresh_cache() const;
};

}
#endif