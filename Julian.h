#ifndef _JULIAN_
#define _JULIAN_

#include <time.h>
#include "WesternDate.h"

namespace lab2 
{

class Julian : public WesternDate {
private:
	// Julian date -> Julian Day Number
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	float date2julianday(int year, int month, int day);

protected:
	bool is_leap_year(int year) const; 

public:
	Julian();
	Julian(int year, int month, int day);
	Julian(const Date& rhs);
	Julian(Date* dp);

	time_t date2timestamp(int year, int month, int day);
	
	// Julian day number -> Julian date
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	void refresh_cache() const;
};

}
#endif
