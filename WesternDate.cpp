#include "WesternDate.h"

namespace lab2 
{

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

const int WesternDate::NUM_WEEK_DAYS = 7;
const int WesternDate::NUM_MONTHS = 12;

WesternDate::WesternDate() : Date() {}
WesternDate::WesternDate(const Date& rhs) : Date(rhs) {}
WesternDate::WesternDate(Date* dp) : Date(dp) {}
WesternDate::~WesternDate() {}

std::string WesternDate::week_day_string(int day) const {
	return WesternDate::WEEK_DAYS[day];
}

std::string WesternDate::month_string(int month) const {
	return WesternDate::MONTHS[month-1];
}

int WesternDate::days_in_a_month(int year, int month) const
{
	month -= 1;
	if (is_leap_year(year) && (month == 1)) {
		return WesternDate::DAYS_IN_A_MONTH[month] + 1;
	}
	return WesternDate::DAYS_IN_A_MONTH[month];
}

bool WesternDate::validate_date(int year, int month, int day) const {
	if (month >= 1 && month <= 12 
		&& day >= 0 && day <= days_in_a_month(year, month)) {
			return true;
	} else {
		throw std::out_of_range("Invalid date!");
	}
}

int WesternDate::days_per_week() const
{
	return NUM_WEEK_DAYS;
}

int WesternDate::months_per_year() const
{
	return NUM_MONTHS;
}

}