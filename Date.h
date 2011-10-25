#ifndef _DATE_
#define _DATE_

#define CACHE_SIZE 4

#define EMPTY -1
#define YEAR 0
#define MONTH 1
#define DAY 2
#define WEEK_DAY 3

#define DAY_IN_SECONDS 86400

class Date 
{
protected:
	static const int days_in_sec[31];
	//TODO Typically calendar specific. Make virtual or move to Western
	static const int days_in_a_month[12]; 

	int cache[CACHE_SIZE];
	
	struct date_struct {
		int year,month,day,week_day;
	};
	
	virtual time_t date2timestamp(int year, int month, int day) = 0;
	virtual date_struct timestamp2date(time_t timestamp) = 0;

	void clear_cache();

	std::string* WEEK_DAYS;
	virtual void populate_week_days() = 0;
	
	void init();

private:
	time_t timestamp;

public:
	// Default constructor sets date to today
	Date() : timestamp( time(&timestamp) ) { this->init(); }

	Date(time_t t) : timestamp(t) { this->init(); }

	virtual ~Date() {}

	// Return unix timestamp of this Date
	time_t get_unix_timestamp() const { return timestamp; }

	Date& set_unix_timestamp(time_t new_timestamp);
	
	void refresh_cache();

	float julian_day() const { return (timestamp / DAY_IN_SECONDS) + 2440587.5; }

	Date& set_julian_day(float jd);
	
	int mod_julian_day() const { return julian_day() - 2400000.5; } 

	int year();

	int month();

	int day();

	int week_day();

	int days_this_month();

	int days_per_week();

	int months_per_year();

	std::string week_day_name();

	std::string month_name();

	/***************
	*** MUTATORS ***
	****************/
	int operator -(const Date& other) const;
	
	Date& add_day(int days);

	Date& add_month(int month);

	Date& add_year(int year);

	Date& operator ++();

	Date& operator --();

	Date& operator +=(int days);

	Date& operator -=(int days);

	/***************
	**COMPARATORS **
	****************/
	bool operator ==(const Date& rhs) const;

	bool operator !=(const Date& rhs) const;

	bool operator <(const Date& rhs) const;

	bool operator <=(const Date& rhs) const;

	bool operator >(const Date& rhs) const;
	
	bool operator >=(const Date& rhs) const;

	friend std::ostream & operator<<(std::ostream & os, Date& date);
	
};

const int days_in_sec[31] = 
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

const int days_in_a_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

#endif