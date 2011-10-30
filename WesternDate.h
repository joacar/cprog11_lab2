#ifndef _WESTERN_DATE_
#define _WESTERN_DATE_

#include <stdexcept>
#include "Date.h"

class WesternDate : public Date {

protected:
	static const std::string WEEK_DAYS[];
	static const std::string MONTHS[];
	static const int DAYS_IN_A_MONTH[];

	virtual bool is_leap_year(int year) = 0;

public:
	WesternDate();
	virtual ~WesternDate();

	std::string week_day_string(int day);
	std::string month_string(int month);

	int days_in_a_month(int year, int month);
	bool validate_date(int year, int month, int day);
};

#endif