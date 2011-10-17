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

class Date {

protected:
	int cache[CACHE_SIZE];
	virtual void refresh_cache() = 0;
	void clear_cache() {
		for(int i = 0; i < CACHE_SIZE; i++){
			cache[i] = EMPTY;
		}
	}

	std::string* WEEK_DAYS;
	virtual void populate_week_days() = 0;
	
	void init() {
		clear_cache();
	}

private:
	// Store dates as UNIX timestamps
	time_t timestamp;

public:
	// Default constructor sets date to today
	Date() : timestamp( time(&timestamp) ) {
		this->init();
	}

	Date(time_t t) : timestamp(t) {
		this->init();
	}

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
		return ( timestamp / 86400 ) + 2440587.5;
	}
	
	int mod_julian_day() const {
		return julian_day() - 2400000.5;
	} 

	int year() {
		if(cache[YEAR] != EMPTY) {
			return cache[YEAR];
		}
		else {
			refresh_cache();
			return cache[YEAR];	
		}
	}

	int month() {
		if(cache[MONTH] != EMPTY) {
			return cache[MONTH];
		}
		else {
			refresh_cache();
			return cache[MONTH];	
		}
	}

	int day() {
		if(cache[DAY] != EMPTY) {
			return cache[DAY];
		}
		else {
			refresh_cache();
			return cache[DAY];	
		}
	}	
	
	int week_day() {
		if(cache[WEEK_DAY] != EMPTY) {
			return cache[WEEK_DAY];
		}
		else {
			refresh_cache();
			return cache[WEEK_DAY];	
		}
	}

	std::string week_day_name(){
		if(cache[WEEK_DAY] != EMPTY) {
			return WEEK_DAYS[cache[WEEK_DAY]];
		}
		else {
			refresh_cache();
			return WEEK_DAYS[cache[WEEK_DAY]];
		}
	}

	int operator -(const Date& other) const {
		time_t difference = timestamp - other.get_unix_timestamp();
		return difference/86400;
	}

	friend std::ostream & operator<<(std::ostream & os, Date& date) {
		os << date.year() << "-" << date.month() << "-" << date.day();
		os << " (" << date.week_day_name() << ")";
		os << " MJD: " << date.mod_julian_day();
		return os;
	}

	virtual ~Date() {}
};

class WesternDate : public Date {

protected:
	void init(){
		populate_week_days();
	}

	WesternDate() : Date() {
		this->init();
	}

	void populate_week_days(){
		WEEK_DAYS = new std::string[7];
		WEEK_DAYS[0] = "Sunday";
		WEEK_DAYS[1] = "Monday";
		WEEK_DAYS[2] = "Tuesday";
		WEEK_DAYS[3] = "Wednesday";
		WEEK_DAYS[4] = "Thursday";
		WEEK_DAYS[5] = "Friday";
		WEEK_DAYS[6] = "Saturday";
	}

	virtual ~WesternDate(){
		delete [] WEEK_DAYS;
	}
};

class Gregorian : public WesternDate {

public:
	Gregorian() : WesternDate() {}
	
	Gregorian(int year, int month, int day) {
		time_t rawtime = time(&rawtime);
		struct tm* given_date = localtime(&rawtime);
		given_date->tm_year = year - 1900;
		given_date->tm_mon = month - 1;
		given_date->tm_mday = day;

		set_unix_timestamp(mktime(given_date));
	}

	void refresh_cache(){
		time_t ts = get_unix_timestamp();
		struct tm* t = localtime(&ts);

		cache[YEAR] = t->tm_year + 1900;
		cache[MONTH] = t->tm_mon + 1;
		cache[DAY] = t->tm_mday;
		cache[WEEK_DAY] = t->tm_wday;
	}	
		
};

class Julian : public WesternDate {

public:
	Julian() : WesternDate() {}

	Julian(int year, int month, int day){}
	
	// Julian day number -> Julian date
	// from http://mysite.verizon.net/aesir_research/date/injdalg2.htm
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
};

int main(){
	Gregorian gtoday;
	std::cout << "Gregorian: " << gtoday << std::endl;
	Julian jtoday;
	std::cout << "Julian: " << jtoday << std::endl;
	return 0;
}