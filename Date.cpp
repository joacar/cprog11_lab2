#include <time.h>
#include <iostream>
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
	const int* DAYS_IN_A_MONTH;
	const std::string* WEEK_DAYS;
	const std::string* MONTHS;

	virtual bool is_leap_year() = 0;
	virtual void refresh_cache() = 0;

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
	Date(const std::string* week_days,
		 const std::string* months,
		 const int* days_in_a_month
		) : timestamp( time(&timestamp) ), WEEK_DAYS(week_days), MONTHS(months), DAYS_IN_A_MONTH(days_in_a_month)
	{ clear_cache(); }

	Date(time_t t,
		 const std::string* week_days,
		 const std::string* months,
		 const int* days_in_a_month
		) : timestamp(t), WEEK_DAYS(week_days), MONTHS(months), DAYS_IN_A_MONTH(days_in_a_month)
	{ clear_cache(); }

	Date(const Date& rhs) 
		: timestamp(rhs.get_unix_timestamp()), WEEK_DAYS(rhs.WEEK_DAYS), MONTHS(rhs.MONTHS), DAYS_IN_A_MONTH(rhs.DAYS_IN_A_MONTH)
	{
		clear_cache();
	}

	Date& operator=(const Date& rhs) {
		if (rhs != *this) {
			set_unix_timestamp(rhs.get_unix_timestamp());
			WEEK_DAYS = rhs.WEEK_DAYS;
			MONTHS = rhs.MONTHS;
			DAYS_IN_A_MONTH = rhs.DAYS_IN_A_MONTH;
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
		return WEEK_DAYS[cache.week_day];	
	}

	std::string month_name(){
		if(cache.month == EMPTY) {
			refresh_cache();
		}
		return MONTHS[cache.month];	
	}

	virtual int days_this_month() {
		return DAYS_IN_A_MONTH[month()];
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

public:
	WesternDate() : Date(WEEK_DAYS, MONTHS, DAYS_IN_A_MONTH) {}
	WesternDate(time_t timestamp) : Date(timestamp, WEEK_DAYS, MONTHS, DAYS_IN_A_MONTH) {}

	virtual ~WesternDate() {}

	int days_this_month()
	{
		int month = this->month()-1;
		if (is_leap_year() && (month == 1)) {
			return Date::DAYS_IN_A_MONTH[month] + 1;
		}
		return Date::DAYS_IN_A_MONTH[month];
	}
};

class Gregorian : public WesternDate {

private:
	float year_in_seconds() { return 365.25*DAYS_IN_SECS[0]; }
	bool is_leap_year()
	{
		int year = this->year();
		return (year % 100 == 0 && year % 400 == 0) || (year % 4 == 0);
	}

public:
	Gregorian() : WesternDate() {}

	Gregorian(time_t timestamp) : WesternDate(timestamp) {}	
	
	Gregorian(int year, int month, int day) {
		// TODO Validation
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

class Julian : public WesternDate {
protected:
	bool is_leap_year() { return year() % 4 == 0; } 

public:
	Julian() : WesternDate() {}

	Julian(time_t timestamp) : WesternDate(timestamp) {}

	Julian(int year, int month, int day){
		// TODO Validation
		set_julian_day(date2julianday(year,month,day));		
	}
	
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