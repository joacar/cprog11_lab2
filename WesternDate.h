#ifndef _WESTERN_DATE_
#define _WESTERN_DATE_

#define NUMBER_MONTHS 12
#define NUMBER_WEEK_DAYS 7

class WesternDate
{
public:
	WesternDate() : Date() {}

private:
	static const int* DAYS_IN_A_MONTH;
	static const std::string* MONTHS;
	static const std::string* WEEK_DAYS;

protected:
	virtual ~WesternDate() {}
	int days_this_month();
};

const int WesternDate::DAYS_IN_A_MONTH[NUMBER_MONTHS] =
	{
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

const std::string WesternDate::WEEK_DAYS[NUMBER_WEEK_DAYS] = 
	{
		"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"
	};

const std::string WesternDate::MONTHS[NUMBER_MONTHS] = 
	{
	"january", "february", "march", "april", "may", "june",
	"july", "august", "september", "october", "november", "december"
	};

#endif