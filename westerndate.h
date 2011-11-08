#ifndef WESTERNDATE_H
#define WESTERNDATE_H

#include "date.h"

namespace lab2 {

class WesternDate : public Date {

protected:
	virtual bool is_leap_year(int year) const = 0;
	virtual bool is_leap_year() const;
	bool validate_date(int year, int month, int day) const;
	int days_in_a_month(int year, int month) const;

public:
	WesternDate();
	WesternDate(const Date& date);

	virtual inline int days_per_week() const { return 7; };
	virtual inline int months_per_year() const {return 12; };
	virtual int days_this_month() const;
	virtual int week_day() const;
	virtual const std::string week_day_name() const;
	virtual const std::string month_name() const;

	void add_month(int = 1);
	void add_year(int = 1);
};

}
#endif