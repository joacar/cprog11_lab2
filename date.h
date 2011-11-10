#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

namespace lab2 {

class Date {

protected:
	mutable struct cache_struct {
		int year, month, day, week_day;	
	} cache;

	int julian_day_number;
	virtual void clear_cache() const;

	virtual void date2julian_day_number(int year, int month, int day) = 0;
	virtual void refresh_cache() const = 0;
	

public:
	Date();
	Date(const Date& date);
	Date(int jdn);
	virtual ~Date();

	friend std::ostream& operator<<(std::ostream& os, const Date& date);

	/***************
	*** GETTERS ****
	****************/
	inline int mod_julian_day() const { return julian_day_number - 2400001; };	// added point five
	inline int year() const { refresh_cache(); return cache.year; };
	inline int month() const { refresh_cache(); return cache.month; };
	inline int day() const { refresh_cache(); return cache.day; };
	
	virtual int week_day() const = 0;
	virtual int days_this_month() const = 0;
	virtual int days_per_week() const = 0;
	virtual int months_per_year() const = 0;
	virtual const std::string week_day_name() const = 0;
	virtual const std::string month_name() const = 0;
	
	/***************
	*** MUTATORS ***
	****************/
	virtual void add_month(int = 1) = 0;
	virtual void add_year(int = 1) = 0;
	inline Date& operator ++() { ++julian_day_number; clear_cache(); return *this; };
	inline Date& operator --() { --julian_day_number; clear_cache(); return *this; };
	inline Date& operator +=(int days) { julian_day_number += days; clear_cache(); return *this; };
	inline Date& operator -=(int days) { julian_day_number -= days; clear_cache(); return *this; };	

	inline int operator -(const Date& rhs) const { return julian_day_number - rhs.julian_day_number; };

	/***************
	** COMPARATORS *
	****************/
	inline bool operator ==(const Date& rhs) const {return julian_day_number == rhs.julian_day_number; };
	inline bool operator !=(const Date& rhs) const {return julian_day_number != rhs.julian_day_number; };
	inline bool operator <(const Date& rhs) const 	{return julian_day_number < rhs.julian_day_number; };
	inline bool operator <=(const Date& rhs) const {return julian_day_number <= rhs.julian_day_number; };
	inline bool operator >(const Date& rhs) const 	{return julian_day_number > rhs.julian_day_number; };
	inline bool operator >=(const Date& rhs) const {return julian_day_number >= rhs.julian_day_number; };
};

}
#endif