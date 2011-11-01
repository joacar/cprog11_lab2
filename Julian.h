#ifndef _JULIAN_
#define _JULIAN_

#include "westerndate.h"

namespace lab2 
{

class Julian : public WesternDate {

protected:
	bool is_leap_year(int year) const; 

public:
	Julian();
	Julian(int year, int month, int day);
	Julian(const Date& rhs);
	Julian(Date* dp);

	// Julian date -> Julian Day Number
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	float date2julian_day_number(int year, int month, int day);
	
	// Julian day number -> Julian date
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	void refresh_cache() const;
};

}
#endif
