#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "westerndate.h"

namespace lab2 
{

class Gregorian : public WesternDate {

	private:
		bool is_leap_year(int year) const;

	public:
		Gregorian();
		Gregorian(const Date& date);
		Gregorian(int year, int month, int day);

		virtual void date2julian_day_number(int year, int month, int day);
		virtual void refresh_cache() const;
};

}
#endif