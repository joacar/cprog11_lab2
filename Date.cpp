#include <time.h>
#include <stdlib.h>
#include <iostream>

#define YEAR 0
#define MONTH 1
#define DAY 2

class Date {

private:
	// Store dates as UNIX timestamps
	time_t timestamp;

	void clear_cache() {
		cache[YEAR] = 0;
		cache[MONTH] = 0;
		cache[DAY] = 0;
	}

protected:
	int cache[3];
	virtual void refresh_cache() = 0;

public:
	// Default constructor sets date to today
	Date() : timestamp( time(&timestamp) ) {
		clear_cache();
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

	int year() {
		if(cache[YEAR]) {
			return cache[YEAR];
		}
		else {
			refresh_cache();
			return cache[YEAR];	
		}
	}

	int month() {
		if(cache[MONTH]) {
			return cache[MONTH];
		}
		else {
			refresh_cache();
			return cache[MONTH];	
		}
	}
	
	int day() {
		if(cache[DAY]) {
			return cache[DAY];
		}
		else {
			refresh_cache();
			return cache[DAY];	
		}
	}	

	friend std::ostream & operator<<(std::ostream & os, Date& date) {
		return os << date.year() << "-" << date.month() << "-" << date.day();
	}

	virtual ~Date() {}
};

class Gregorian : public Date {

public:
	Gregorian() : Date() {}
	
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
	}	
		
};

class Julian : public Date {

public:
	Julian() : Date() {}
	
	void refresh_cache() {}	
};

int main(){
	Gregorian gtoday;
	std::cout << "Today's Gregorian date is: " << gtoday << std::endl;

	Julian jtoday;
	std::cout << "Today's Julian date is: " << jtoday << std::endl;		

	return 0;
}