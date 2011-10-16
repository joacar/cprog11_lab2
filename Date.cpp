#include <time.h>
#include <stdlib.h>
#include <iostream>

class Date
{
protected:

	// Store dates as UNIX timestamps
	time_t date;

public:
	
	// Default constructor sets date to today
	Date() : date( time(&date) ) {}

	// // Create a date object given a certain Unix timestamp
	// Date(time_t given_date) : date( given_date ) {}

	// // Copy constructor - copy date from other Date into our own
	// Date(const Date& other) : date( other.date ) {}

	// Return unix timestamp of this Date
	time_t get_unix_timestamp() const {
		return date;
	}

	// Get year from this.date
	virtual int year() = 0;
	// Get month from this.date
	virtual int month() = 0;
	// Get day from this.day
	virtual int day() = 0;

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

		date = mktime(given_date);
	}

	int year() {
		struct tm* t = localtime(&date);
		return (t->tm_year + 1900);
	}

	int month() {
		struct tm* t = localtime(&date);
		return (t->tm_mon + 1);
	}

	int day() {
		struct tm* t = localtime(&date);
		return (t->tm_mday);
	}	
};

class Julian : public Date {

public:
	Julian() : Date() {}

	int julian_day() {
		return ( date / 86400 ) + 2440587;
	}

	int year() {
		return julian_day() / 365;	
	}

	int month() {
		return (julian_day() % 365) / 12;
	}

	int day() {
		return ((julian_day() % 365) % 12) / 31;
	}	
};

int main(){
	Gregorian gtoday;
	std::cout << "Today's Gregorian date is: " << gtoday << std::endl;

	Julian jtoday;
	std::cout << "Today's Julian day number is: " << jtoday.julian_day() << std::endl;
	std::cout << "Today's Julian date is: " << jtoday << std::endl;		

	return 0;
}