#include <time.h>
#include <iostream>
#include <string>

#define CACHE_SIZE 4

#define YEAR 0
#define MONTH 1
#define DAY 2
#define WEEK_DAY 3

class Date {

protected:
	int cache[CACHE_SIZE];
	virtual void refresh_cache() = 0;

private:
	// Store dates as UNIX timestamps
	time_t timestamp;

	void clear_cache() {
		for(int i = 0; i < CACHE_SIZE; i++){
			cache[i] = 0;
		}
	}

public:
	// Default constructor sets date to today
	Date() : timestamp( time(&timestamp) ) {
		clear_cache();
	}

	Date(time_t t) : timestamp(t) {
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
	
	int week_day() {
		if(cache[WEEK_DAY]) {
			return cache[WEEK_DAY];
		}
		else {
			refresh_cache();
			return cache[WEEK_DAY];	
		}
	}

	virtual std::string week_day_name() = 0;

	int operator -(const Date& other) const {
		time_t difference = timestamp - other.get_unix_timestamp();
		return difference/86400;
	}

	friend std::ostream & operator<<(std::ostream & os, Date& date) {
		return os << date.year() << "-" << date.month() << "-" << date.day() << ": " << date.week_day_name();
	}

	virtual ~Date() {}
};

class Gregorian : public Date {

private:
	std::string WEEK_DAYS[8];

	void populate_week_days(){
		WEEK_DAYS[1] = "Sunday";
		WEEK_DAYS[2] = "Monday";
		WEEK_DAYS[3] = "Tuesday";
		WEEK_DAYS[4] = "Wednesday";
		WEEK_DAYS[5] = "Thursday";
		WEEK_DAYS[6] = "Friday";
		WEEK_DAYS[7] = "Saturday";
	}

public:

	Gregorian() : Date() {
		populate_week_days();
	}
	
	Gregorian(int year, int month, int day) {
		populate_week_days();

		time_t rawtime = time(&rawtime);
		struct tm* given_date = localtime(&rawtime);
		given_date->tm_year = year - 1900;
		given_date->tm_mon = month - 1;
		given_date->tm_mday = day;

		set_unix_timestamp(mktime(given_date));
	}

	std::string week_day_name(){
		if(cache[WEEK_DAY]) {
			return WEEK_DAYS[cache[WEEK_DAY]];
		}
		else {
			refresh_cache();
			return WEEK_DAYS[cache[WEEK_DAY]];
		}
	}

	void refresh_cache(){
		time_t ts = get_unix_timestamp();
		struct tm* t = localtime(&ts);

		cache[YEAR] = t->tm_year + 1900;
		cache[MONTH] = t->tm_mon + 1;
		cache[DAY] = t->tm_mday;
		cache[WEEK_DAY] = t->tm_wday + 1;
	}	
		
};

class Julian : public Date {

public:
	Julian() : Date() {}
	
	void refresh_cache() {}	

	std::string week_day_name(){
		return "Tuesday";
	}
};

int main(){
	Gregorian today;
	Gregorian my_birthday = Gregorian(1995,06,20);		
	std::cout << today - my_birthday << " days ago, you were born on " << my_birthday << std::endl;
	return 0;
}