#include <time.h>
#include <iostream>
#include <string>
#include <math.h>

#define CACHE_SIZE 4

#define EMPTY -1
#define YEAR 0
#define MONTH 1
#define DAY 2
#define WEEK_DAY 3

#define DAY_IN_SECONDS 86400

const int Date::days_in_sec[31] = 
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

class Date {

protected:
	struct date_struct {
		int year,month,day,week_day;
	};

	date_struct cache = {EMPTY,EMPTY,EMPTY,EMPTY};
	
	static const int* days_in_sec;
	static const std::string* WEEK_DAYS;
	static const std::string* MONTHS;
	static const int* days_in_a_month;

	virtual void populate_week_days() = 0;
	virtual int days_this_month() = 0;
	virtual bool is_leap_year() = 0;
	virtual time_t date2timestamp(int year, int month, int day) = 0;
	virtual void timestamp2cache(time_t timestamp) = 0;

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
	Date() : timestamp( time(&timestamp) ) {}

	Date(time_t t) : timestamp(t) {}

	Date(const Date& rhs) : timestamp(rhs.get_unix_timestamp()) {}

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
	
	void refresh_cache() {
		timestamp2cache(timestamp);
	}

	float julian_day() const {
		return (timestamp / DAY_IN_SECONDS) + 2440587.5;
	}

	Date& set_julian_day(float jd) {
		int ts = (int) ((jd - 2440587.5) * DAY_IN_SECONDS);
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
		return WEEK_DAYS[cache.week_day];	
	}

	std::string month_name(){
		if(cache.month == EMPTY) {
			refresh_cache();
		}
		return MONTHS[cache.month];	
	}

	/***************
	*** MUTATORS ***
	****************/
	int operator -(const Date& other) const {
		time_t difference = timestamp - other.get_unix_timestamp();
		return difference/DAY_IN_SECONDS;
	}
	
	Date& add_day(int days) {
		if (days >= -31 && days < 0) {
			return set_unix_timestamp(timestamp - days_in_sec[days-1]);
		}
		if (days <= 31) {
			return set_unix_timestamp(timestamp + days_in_sec[days-1]);
		} 
		return set_unix_timestamp(timestamp + days*DAY_IN_SECONDS);
	}

	Date& operator ++() { return add_day(1); }

	Date& operator --() { return add_day(-1); }

	Date& operator +=(int days) { return add_day(days); }

	Date& operator -=(int days) { return add_day(-days); }	

	Date& add_month(int month)
	{
		/*if day_in_next_month_in_same_year
			set_unix_timestamp(date2timestamp(year(), month()+1, day()));
		else if not day_in_next_month_in_same_year
			set_unix_timestamp(timestamp + days[29]);
		else if FUCK ITS FEBRUARY 29*/
		return *this;
	}

	Date& add_year(int year)
	{
		/*if same_day_next_year
			set_unix_timestamp(date2timestamp(year()+1,month(),day()));
		else if FUCK ITS FEBRUARY 29*/
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
		std::string month, day;
		if(date.month() < 10)
			month = "0" + date.month();
		if(date.day() < 10)
			day = "0" + date.month();
		
		os << date.year() << "-" << month << "-" << day;
		os << " (" << date.week_day_name() << ")";
		os << " MJD: " << date.mod_julian_day();
		return os;
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

class WesternDate : public Date {

protected:
	virtual ~WesternDate() {}
	
	int days_this_month()
	{
		int month = this->month()-1;
		if (is_leap_year() && MONTHS[month] == 'february') {
			return days_in_a_month[month] + 1;
		}
		return days_in_a_month[month];
	}

public:
	WesternDate() : Date() {}
	WesternDate(time_t timestamp) : Date(timestamp) {}
};

class Gregorian : public WesternDate {

private:
	float year_in_seconds() { return 365.25*DAY_IN_SECONDS; }
	bool is_leap_year()
	{
		int year = this->year();
		return (year % 100 == 0 && year % 400 == 0) || (year % 4 == 0);
	}

public:
	Gregorian() : WesternDate() {}

	Gregorian(time_t timestamp) : WesternDate(timestamp) {}	
	
	Gregorian(int year, int month, int day) : cache.year(year), cache.month(month), cache.day(day) {
		set_unix_timestamp(date2timestamp(year,month,day));
	}

	time_t date2timestamp(int year, int month, int day)
	{
		time_t rawtime = time(&rawtime);
		struct tm* given_date = localtime(&rawtime);
		given_date->tm_year = year - 1900;
		given_date->tm_mon = month - 1;
		given_date->tm_mday = day;
		return mktime(given_date);	
	}

	void timestamp2cache(time_t timestamp)
	{
		struct tm* t = localtime(&timestamp);
		cache.year = t->tm_year + 1900;
		cache.month = t->tm_mon + 1;
		cache.day = t->tm_mday;
		cache.week_day = t->tm_wday;
	}
};

class Julian : public WesternDate {
protected:
	bool is_leap_year() { return year() % 4 == 0; } 

public:
	Julian() : WesternDate() {}

	// Julian date -> Julian Day Number -> timestamp
	// from http://mysite.verizon.net/aesir_research/date/date0.htm
	Julian(int year, int month, int day){
		if (month < 3) {
			month = month + 12;
			year = year - 1;
		}
		float julian_day = day + (153*month-457)/5 + 365*year + year/4 + 1721116.5;
		set_julian_day(julian_day);
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

		cache[DAY] = c - f + r;
		if (m > 12) {
			y = y + 1;
			m = m - 12;
		}
		cache[YEAR] = y;
		cache[MONTH] = m;
		cache[WEEK_DAY] = 1; // <-- TODO FIX THIS
	}

	time_t date2timestamp(int year, int month, int day)
	{
		return 0;
	}

	date_struct timestamp2date(time_t timestamp)
	{
		date_struct ds;
		return ds;
	}
};

int main(){
	Gregorian gtoday;
	std::cout << "Gregorian: " << gtoday << std::endl;
	Julian jtoday;
	std::cout << "Julian: " << jtoday << std::endl;

	std::cout << "I was born on: " << std::endl;	
	Gregorian gbirthday = Gregorian(1988,12,16);
	std::cout << gbirthday << std::endl;
	Julian jbirthday = Julian(1988,12,16);
	std::cout << jbirthday << std::endl;
		
	return 0;
}