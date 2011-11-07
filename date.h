#ifndef _DATE_
#define _DATE_

#include <iostream>
#include <string>

namespace lab2 
{

class Date {

private:
	float julian_day_number;

protected:
	mutable struct cache_struct {
		int year,month,day,week_day;
	} cache;
	
	static const int DAYS_IN_SECS[];
	static int round(float f);

	virtual float date2julian_day_number(int year, int month, int day) = 0;
	virtual void refresh_cache() const = 0;

	virtual std::string week_day_string(int day) const = 0;
	virtual std::string month_string(int month) const = 0;
	virtual int days_in_a_month(int year, int month) const = 0;
	virtual bool validate_date(int year, int month, int day) const = 0;
	void clear_cache() const;

public:
	Date();
	Date(const Date& rhs);
	Date(Date* dp);
	Date& operator=(const Date& rhs);
	virtual ~Date();

	float get_julian_day_number() const;
	Date& set_julian_day_number(float jd);
	
	int mod_julian_day() const;
	int year() const;
	int month() const;
	int day() const;	
	int week_day() const;
	std::string week_day_name() const;
	std::string month_name() const;
	int days_this_month() const;
	virtual int days_per_week() const = 0;
	virtual int months_per_year() const = 0;


	/***************
	*** MUTATORS ***
	****************/
	Date& add_day(int days);
	Date& add_month(int months);
	Date& add_month();
	Date& add_year(int years);
	Date& add_year();

	int operator -(const Date& other) const;
	Date& operator ++();
	Date& operator --();
	Date& operator +=(int days);
	Date& operator -=(int days);
	friend std::ostream& operator<<(std::ostream & os, const Date& d);	

	/***************
	**COMPARATORS **
	****************/
	bool operator ==(const Date& rhs) const;
	bool operator !=(const Date& rhs) const;
	bool operator <(const Date& rhs) const;
	bool operator <=(const Date& rhs) const;
	bool operator >(const Date& rhs) const;
	bool operator >=(const Date& rhs) const;
};

}
#endif