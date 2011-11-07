#include <time.h>
#include <stdexcept>
#include <string>
#include <math.h>

#include "kattistime.h"
#include "date.h"

#define EMPTY -1
#define DAY_IN_SECONDS 86400.0
#define DEBUG 0

namespace lab2 {

int Date::round(double f) {
	return (f > 0.0) ? floor(f + 0.5) : ceil(f - 0.5);
}

// Default constructor sets date to today
Date::Date() { 
	time_t timestamp;
	timestamp = k_time(&timestamp);
	set_julian_day_number((timestamp/DAY_IN_SECONDS) + 2440587.5);
}
Date::Date(const Date& rhs) : julian_day_number(rhs.get_julian_day_number()) { clear_cache(); }
Date::Date(Date* dp) : julian_day_number(dp->get_julian_day_number()) { clear_cache(); }

Date& Date::operator=(const Date& rhs) {
	if (rhs != *this) {
		set_julian_day_number(rhs.get_julian_day_number());
	}
	return *this;
}

Date::~Date() {}

// Return Julian Day Number of this Date
double Date::get_julian_day_number() const {
	return julian_day_number;
}

Date& Date::set_julian_day_number(double new_julian_day_number) {
	julian_day_number = new_julian_day_number;
	clear_cache();
	return *this;
}

void Date::clear_cache() const {
	cache.year = EMPTY;
	cache.month = EMPTY;
	cache.day = EMPTY;
	cache.week_day = EMPTY;
}

int Date::mod_julian_day() const {
	double mjd = get_julian_day_number() - 2400000.5;
	return round(mjd);  
} 

int Date::year() const {
	if(cache.year == EMPTY) {
		refresh_cache();
	}
	return cache.year;
}

int Date::month() const {
	if(cache.month == EMPTY) {
		refresh_cache();
	}
	return cache.month;
}

int Date::day() const {
	if(cache.day == EMPTY) {
		refresh_cache();
	}
	return cache.day;
}	

int Date::week_day() const {
	if(cache.week_day == EMPTY) {
		refresh_cache();
	}
	return cache.week_day + 1;
}

std::string Date::week_day_name() const {
	if(cache.week_day == EMPTY) {
		refresh_cache();
	}
	return week_day_string(cache.week_day);	
}

std::string Date::month_name() const {
	if(cache.month == EMPTY) {
		refresh_cache();
	}
	return month_string(cache.month);	
}

int Date::days_this_month() const {
	return days_in_a_month(year(), month());
}

/***************
*** MUTATORS ***
****************/
int Date::operator-(const Date& other) const {
	return julian_day_number - other.get_julian_day_number();
}

Date& Date::add_day(int days) {
	return set_julian_day_number(julian_day_number + days);
}

Date& Date::operator ++() { return add_day(1); }

Date& Date::operator --() { return add_day(-1); }

Date& Date::operator +=(int days) { return add_day(days); }

Date& Date::operator -=(int days) { return add_day(-days); }

std::ostream& operator<<(std::ostream & os, const Date& d) {
	os << d.year() << "-";
	if (d.month() < 10)
		os << "0"; 
	os << d.month() << "-";
	if (d.day() < 10)
		os << "0";
	os << d.day();
	if(DEBUG) {
		os << " <" << d.week_day_name() << ", "<< d.get_julian_day_number() << " (jd) , " << d.mod_julian_day() << "(mod) > ";
	}
	return os;
}	

Date& Date::add_month(int months)
{
	int year_num = year();
	int month_num = month() + months;

	// Adjust if rolling over year boundaries
	// Positive case
	if(month_num > 12) {
		year_num += month_num/12;
		month_num = month_num % 12;
	}

	// Negative case
	if(months < 0) {
		year_num += months/12;
		month_num = (month_num % 12) + 12;
	}		

	try {
		set_julian_day_number(date2julian_day_number(year_num, month_num, day()));
	} catch(std::out_of_range& e) {
		set_julian_day_number(julian_day_number + 30);
	}
	return *this;
}

Date& Date::add_month()
{
	return add_month(1);
}

Date& Date::add_year()
{
	return add_year(1);
}

Date& Date::add_year(int years)
{
	try {
		set_julian_day_number(date2julian_day_number(year()+years, month(), day()));
	} catch(std::out_of_range& e) {
		// Leap year, 29 Feb -> 28 Feb
		set_julian_day_number(date2julian_day_number(year()+years, month(), day()-1));
	}
	return *this;
}

/***************
**COMPARATORS **
****************/
bool Date::operator ==(const Date& rhs) const	{ return !(*this-rhs); }

bool Date::operator !=(const Date& rhs) const	{ return !(*this==rhs); }

bool Date::operator <(const Date& rhs) const { return (*this-rhs) < 0 ? true : false; }

bool Date::operator <=(const Date& rhs) const	{ return (*this-rhs) <= 0 ? true : false; }

bool Date::operator >(const Date& rhs) const { return (*this-rhs) > 0 ? true : false; }

bool Date::operator >=(const Date& rhs) const	{ return (*this-rhs) >= 0 ? true : false; }

}