#ifndef JULIAN_H
#define JULIAN_H

#include "westerndate.h"

namespace lab2 
{

class Julian : public WesternDate {

protected:
	inline bool is_leap_year(int year) const { return year % 4 == 0; }; 

public:
	Julian();
	Julian(const Date& date);
	Julian(int year, int month, int day);

	// Julian date -> Julian Day Number
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	virtual void date2julian_day_number(int year, int month, int day);
	
	// Julian day number -> Julian date
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	virtual void refresh_cache() const;
};

}
#endif
