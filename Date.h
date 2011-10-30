#ifndef _DATE_
#define _DATE_

#include <time.h>
#include <iostream>
#include <string>

class Date {

private:
	time_t timestamp;

protected:
	struct cache_struct {
		int year,month,day,week_day;
	} cache;
	
	static const int DAYS_IN_SECS[];

	virtual time_t date2timestamp(int year, int month, int day) = 0;
	virtual void refresh_cache() = 0;

	virtual std::string week_day_string(int day) = 0;
	virtual std::string month_string(int month) = 0;
	virtual int days_in_a_month(int year, int month) = 0;
	virtual bool validate_date(int year, int month, int day) = 0;

	void clear_cache();

public:
	Date();
	Date(const Date& rhs);
	Date& operator=(const Date& rhs);
	virtual ~Date();

	time_t get_unix_timestamp() const;
	Date& set_unix_timestamp(time_t new_timestamp);

	float julian_day() const;
	Date& set_julian_day(float jd);
	
	int mod_julian_day() const;
	int year();
	int month();
	int day();	
	int week_day();
	std::string week_day_name();
	std::string month_name();
	int days_this_month();

	/***************
	*** MUTATORS ***
	****************/
	Date& add_day(int days);
	Date& add_month(int months);
	Date& add_year(int years);

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

#endif