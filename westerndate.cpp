#include "westerndate.h"

#include <stdexcept>

namespace lab2  {

WesternDate::WesternDate() : Date() {}
WesternDate::WesternDate(const Date& d) : Date(d) {}

int WesternDate::days_this_month() const 
{	
	return days_in_a_month(year(), month()); 
}

int WesternDate::week_day() const
{
	return julian_day_number % 7 + 1;
}

const std::string WesternDate::week_day_name() const
{
	static const std::string days_names[] = { "ONE_INDEX", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };
	return days_names[week_day()];
}

const std::string WesternDate::month_name() const {
	static const std::string months_names[] = { "ONE_INDEX", "january", "february", "march", "april", "may", "june",
	"july", "august", "september", "october", "november", "december"
	};
	return months_names[month()];
}

int WesternDate::days_in_a_month(int year, int month) const {
	static const int days_per_month[] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (is_leap_year(year) && month == 2) {
		return 29;
	}
	return days_per_month[month];
}

bool WesternDate::is_leap_year() const { 
	return is_leap_year(year()); 
}

bool WesternDate::validate_date(int year, int month, int day) const {
	if ( year < 1858 || year > 2558
		|| month <= 0 || month > months_per_year() 
		|| day <= 0 || day > days_in_a_month(year, month)) {
			return false;
	}
	return true;
}

void WesternDate::add_month(int months) {
	int year_num = year();
	int month_num = month() + months;

	// Adjust if rolling over year boundaries
	// Positive case
	if(month_num > 12) {
		year_num += month_num/12;
		month_num = month_num % 12;
	}

	// Negative case
	if(months < 0) {
		year_num += month_num/12;
		month_num = (month_num % 12) + 12;
	}		

	int day_num = day();
	if(!validate_date( year_num, month_num, day_num ) ) {
		day_num = 30;
	}

	date2julian_day_number( year_num, month_num, day_num );
	set_julian_day_number( julian_day_number );
}

void WesternDate::add_year(int years) {
	int year_ = year() + years;
	int month_ = month();
	int day_ = day();

	if(!validate_date(year_, month_, day_)) {
		day_ -= 1;
	}

	date2julian_day_number( year_, month_, day_);
	set_julian_day_number( julian_day_number );	
}

}