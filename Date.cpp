#include <time.h>
#include "kattistime.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <math.h>


#define EMPTY -1
#define DAY_IN_SECONDS 86400

class Date {

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

	void clear_cache() {
		cache.year = EMPTY;
		cache.month = EMPTY;
		cache.day = EMPTY;
		cache.week_day = EMPTY;
	}

private:
	// Store dates as UNIX timestamps
	time_t timestamp;

public:
	// Default constructor sets date to today
	Date() : timestamp( /*k_time(&timestamp)*/ time(&timestamp) ) { clear_cache(); }
	Date(const Date& rhs) : timestamp(rhs.get_unix_timestamp()) { clear_cache(); }

	Date& operator=(const Date& rhs) {
		if (rhs != *this) {
			set_unix_timestamp(rhs.get_unix_timestamp());
		}
		return *this;
	}

	virtual ~Date() {}

	// Return unix timestamp of this Date
	time_t get_unix_timestamp() const {
		return timestamp;
	}

	Date& set_unix_timestamp(time_t new_timestamp) {
		timestamp = new_timestamp;
		clear_cache();
		return *this;
	}

	float julian_day() const {
		return (timestamp / DAYS_IN_SECS[0]) + 2440587.5;
	}

	Date& set_julian_day(float jd) {
		int ts = (int) ((jd - 2440587.5) * DAYS_IN_SECS[0]);
		return set_unix_timestamp(ts);
	}
	
	int mod_julian_day() const {
		return julian_day() - 2400000.5;
	} 

	int year() {
		if(cache.year == EMPTY) {
			refresh_cache();
		}
		return cache.year;
	}

	int month() {
		if(cache.month == EMPTY) {
			refresh_cache();
		}
		return cache.month;
	}

	int day() {
		if(cache.day == EMPTY) {
			refresh_cache();
		}
		return cache.day;
	}	
	
	int week_day() {
		if(cache.week_day == EMPTY) {
			refresh_cache();
		}
		return cache.week_day;
	}

	std::string week_day_name(){
		if(cache.week_day == EMPTY) {
			refresh_cache();
		}
		return week_day_string(cache.week_day);	
	}

	std::string month_name(){
		if(cache.month == EMPTY) {
			refresh_cache();
		}
		return month_string(cache.month);	
	}

	virtual int days_this_month() {
		return days_in_a_month(year(), month());
	}

	/***************
	*** MUTATORS ***
	****************/
	int operator -(const Date& other) const {
		time_t difference = timestamp - other.get_unix_timestamp();
		return difference/DAYS_IN_SECS[0];
	}
	
	Date& add_day(int days) {
		if (days >= -31 && days < 0) {
			return set_unix_timestamp(timestamp - DAYS_IN_SECS[days-1]);
		}
		if (days <= 31) {
			return set_unix_timestamp(timestamp + DAYS_IN_SECS[days-1]);
		} 
		return set_unix_timestamp(timestamp + days*DAYS_IN_SECS[0]);
	}

	Date& operator ++() { return add_day(1); }

	Date& operator --() { return add_day(-1); }

	Date& operator +=(int days) { return add_day(days); }

	Date& operator -=(int days) { return add_day(-days); }	

	Date& add_month(int months)
	{
		try {
			set_unix_timestamp(date2timestamp(year(), month()+months, day()));
		} catch(std::out_of_range& e) {
			set_unix_timestamp(timestamp + DAYS_IN_SECS[29]);
		}
		return *this;
	}

	Date& add_year(int years)
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
	bool operator ==(const Date& rhs) const	{ return !(*this-rhs); }

	bool operator !=(const Date& rhs) const	{ return !(*this==rhs); }

	bool operator <(const Date& rhs) const { return (*this-rhs) < 0 ? true : false; }

	bool operator <=(const Date& rhs) const	{ return (*this-rhs) <= 0 ? true : false; }

	bool operator >(const Date& rhs) const { return (*this-rhs) > 0 ? true : false; }
	
	bool operator >=(const Date& rhs) const	{ return (*this-rhs) >= 0 ? true : false; }

	friend std::ostream & operator<<(std::ostream & os, Date& date) {
		os << date.year() << "-" << date.month() << "-" << date.day();
		os << " (" << date.week_day_name() << ")";
		os << " MJD: " << date.mod_julian_day();
		return os;
	}

};

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

class WesternDate : public Date {

protected:
	static const std::string WEEK_DAYS[];
	static const std::string MONTHS[];
	static const int DAYS_IN_A_MONTH[];

	virtual bool is_leap_year(int year) = 0;

public:
	WesternDate() : Date() {}

	virtual ~WesternDate() {}

	std::string week_day_string(int day) {
		return WesternDate::WEEK_DAYS[day];
	}
	
	std::string month_string(int month) {
		return WesternDate::MONTHS[month-1];
	}

	int days_in_a_month(int year, int month)
	{
		month -= 1;
		if (is_leap_year(year) && (month == 1)) {
			return WesternDate::DAYS_IN_A_MONTH[month] + 1;
		}
		return WesternDate::DAYS_IN_A_MONTH[month];
	}

	bool validate_date(int year, int month, int day) {
		if (month >= 1 && month <= 12 
			&& day >= 0 && day <= days_in_a_month(year, month)) {
				return true;
			} else {
				throw std::out_of_range("Invalid date!");
			}
	}
};

const std::string WesternDate::WEEK_DAYS[] = {
	"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"
};

const std::string WesternDate::MONTHS[] = {
	"january", "february", "march", "april", "may", "june",
	"july", "august", "september", "october", "november", "december"
};

const int WesternDate::DAYS_IN_A_MONTH[] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

class Gregorian : public WesternDate {

private:
	float year_in_seconds() { return 365.25*DAYS_IN_SECS[0]; }
	bool is_leap_year(int year)
	{
		return (year % 100 == 0 && year % 400 == 0) || (year % 4 == 0);
	}

public:
	Gregorian() : WesternDate() {}	

	Gregorian(int year, int month, int day) {
		set_unix_timestamp(date2timestamp(year,month,day));
	}

	time_t date2timestamp(int year, int month, int day)
	{
		validate_date(year, month, day);

		time_t rawtime = 0;
		//k_time(&rawtime);
		//time(&rawtime);
		struct tm* given_date = localtime(&rawtime);
		given_date->tm_year = year - 1900;
		given_date->tm_mon = month - 1;
		given_date->tm_mday = day;
		return mktime(given_date);	
	}

	void refresh_cache()
	{
		time_t timestamp = get_unix_timestamp();
		const struct tm* t = localtime(&timestamp);
		cache.year = t->tm_year + 1900;
		cache.month = t->tm_mon + 1;
		cache.day = t->tm_mday;
		cache.week_day = t->tm_wday;
	}
};

class Julian : public WesternDate {
private:
	// Julian date -> Julian Day Number
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	float date2julianday(int year, int month, int day) {
		if (month < 3) {
			month = month + 12;
			year = year - 1;
		}
		float julian_day = day + (153*month-457)/5 + 365*year + year/4 + 1721116.5;
		return julian_day;
	}

protected:
	bool is_leap_year(int year) { return year % 4 == 0; } 

public:
	Julian() : WesternDate() {}

	Julian(int year, int month, int day) {
		set_unix_timestamp(date2timestamp(year,month,day));
	}

	time_t date2timestamp(int year, int month, int day) {
		validate_date(year, month, day);
		return (time_t) (date2julianday(year,month,day) - 2440587.5)*DAYS_IN_SECS[0];
	}
	
	// Julian day number -> Julian date
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	void refresh_cache() {
		float jd = julian_day();
		int z = (int) floor(jd - 1721116.5);
		float r = (jd - 1721116.5) - z;
		int y = (int) floor((z-0.25)/365.25);
		int c = (int) (z - floor(365.25*y));
		int m = (5*c + 456)/153;
		int f = (153*m-457)/5;

		cache.day = c - f + r;
		if (m > 12) {
			y = y + 1;
			m = m - 12;
		}
		cache.year = y;
		cache.month = m;
		cache.week_day = 1; // <-- TODO FIX THIS
	}
};

int main(){
	// Set kattistime to right now
	// time_t time_now;
	// time(&time_now);
	// set_k_time(time_now);

	Gregorian gtoday;
	std::cout << "Gregorian: " << gtoday << std::endl;
	Julian jtoday;
	std::cout << "Julian: " << jtoday << std::endl;

	std::cout << "Gregorian(2012,2,29) - 1 year + 1 year" << std::endl;	
	Gregorian gleap = Gregorian(2012,2,29);
	gleap.add_year(-1).add_year(1);
	std::cout << gleap << std::endl;

	return 0;
}