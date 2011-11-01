#ifndef _WESTERN_DATE_
#define _WESTERN_DATE_

#include <stdexcept>
#include "date.h"

namespace lab2
{

class WesternDate : public Date {

protected:
	static const int NUM_WEEK_DAYS;
	static const int NUM_MONTHS;
	static const std::string WEEK_DAYS[];
	static const std::string MONTHS[];
	static const int DAYS_IN_A_MONTH[];

	virtual bool is_leap_year(int year) const = 0;

public:
	WesternDate();
	WesternDate(const Date& date);
	WesternDate(Date* dp);
	virtual ~WesternDate();

	std::string week_day_string(int day) const;
	std::string month_string(int month) const;

	int days_in_a_month(int year, int month) const;
	bool validate_date(int year, int month, int day) const;
	int days_per_week() const;
	int months_per_year() const; 

};

}
#endif