#include <time.h>
#include <stdexcept>
#include <string>
#include <math.h>

#include "kattistime.h"
#include "Date.h"

#define EMPTY -1
#define DAY_IN_SECONDS 86400

namespace lab2 { 
const int Date::DAYS_IN_SECS[] = 
{
	DAY_IN_SECONDS*1,
	DAY_IN_SECONDS*2,
	DAY_IN_SECONDS*3,
	DAY_IN_SECONDS*4,
	DAY_IN_SECONDS*5,
	DAY_IN_SECONDS*6,
	DAY_IN_SECONDS*7,
	DAY_IN_SECONDS*8,
	DAY_IN_SECONDS*9,
	DAY_IN_SECONDS*10,
	DAY_IN_SECONDS*11,
	DAY_IN_SECONDS*12,
	DAY_IN_SECONDS*13,
	DAY_IN_SECONDS*14,
	DAY_IN_SECONDS*15,
	DAY_IN_SECONDS*16,
	DAY_IN_SECONDS*17,
	DAY_IN_SECONDS*18,
	DAY_IN_SECONDS*19,
	DAY_IN_SECONDS*20,
	DAY_IN_SECONDS*21,
	DAY_IN_SECONDS*22,
	DAY_IN_SECONDS*23,
	DAY_IN_SECONDS*24,
	DAY_IN_SECONDS*25,
	DAY_IN_SECONDS*26,
	DAY_IN_SECONDS*27,
	DAY_IN_SECONDS*28,
	DAY_IN_SECONDS*29,
	DAY_IN_SECONDS*30,
	DAY_IN_SECONDS*31
};

// Default constructor sets date to today
Date::Date() : timestamp( k_time(&timestamp) ) { clear_cache(); }
Date::Date(const Date& rhs) : timestamp(rhs.get_unix_timestamp()) { clear_cache(); }
Date::Date(Date* dp) : timestamp(dp->get_unix_timestamp()) { clear_cache(); }

Date& Date::operator=(const Date& rhs) {
	if (rhs != *this) {
		set_unix_timestamp(rhs.get_unix_timestamp());
	}
	return *this;
}

Date::~Date() {}

// Return unix timestamp of this Date
time_t Date::get_unix_timestamp() const {
	return timestamp;
}

Date& Date::set_unix_timestamp(time_t new_timestamp) {
	timestamp = new_timestamp;
	clear_cache();
	return *this;
}

void Date::clear_cache() const {
	cache.year = EMPTY;
	cache.month = EMPTY;
	cache.day = EMPTY;
	cache.week_day = EMPTY;
}

float Date::julian_day() const {
	return (timestamp / DAYS_IN_SECS[0]) + 2440587.5;
}

Date& Date::set_julian_day(float jd) {
	int ts = (int) ((jd - 2440587.5) * DAYS_IN_SECS[0]);
	return set_unix_timestamp(ts);
}

int Date::mod_julian_day() const {
	return julian_day() - 2400000.5;
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
	return cache.week_day;
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
	time_t difference = timestamp - other.get_unix_timestamp();
	return difference/DAYS_IN_SECS[0];
}

Date& Date::add_day(int days) {
	if (days >= -31 && days < 0) {
		return set_unix_timestamp(timestamp - DAYS_IN_SECS[-1*days-1]);
	}
	if (days <= 31) {
		return set_unix_timestamp(timestamp + DAYS_IN_SECS[days-1]);
	} 
	return set_unix_timestamp(timestamp + days*DAYS_IN_SECS[0]);
}

Date& Date::operator ++() { return add_day(1); }

Date& Date::operator --() { return add_day(-1); }

Date& Date::operator +=(int days) { return add_day(days); }

Date& Date::operator -=(int days) { return add_day(-days); }

std::ostream& operator<<(std::ostream & os, const Date& d) {
	os << d.year() << "-" << d.month() << "-" << d.day();
	os << " (" << d.week_day_name() << ")";
	os << " MJD: " << d.mod_julian_day();
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
		set_unix_timestamp(date2timestamp(year_num, month_num, day()));
	} catch(std::out_of_range& e) {
		set_unix_timestamp(timestamp + DAYS_IN_SECS[29]);
	}
	return *this;
}

Date& Date::add_month()
{
	return add_month(1);
}

Date& Date::add_year(int years)
{
	try {
		set_unix_timestamp(date2timestamp(year()+years, month(), day()));
	} catch(std::out_of_range& e) {
		// Leap year, 29 Feb -> 28 Feb
		set_unix_timestamp(date2timestamp(year()+years, month(), day()-1));
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