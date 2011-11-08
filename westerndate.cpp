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
	int nr_months = (months < 0 ? -1*months : months);
	int step = (months < 0 ? -1 : 1);

	for(int i = 0; i < nr_months; ++i) {
		int year_ = year();
		int month_ = month();
		int day_ = day();

		month_ += step;

		if(month_ > months_per_year()) {
			year_ += 1;
			month_ = 1;
		}
		if(month_ <= 0) {
			year_ -= 1;
			month_ = months_per_year();
		}

		if(day_ > days_in_a_month(year_, month_)) {
			*this += 30*step;
		} else {
			date2julian_day_number( year_, month_, day_ );	
		}
		clear_cache();
	}
}

void WesternDate::add_year(int years) {
	int year_ = year() + years;
	int month_ = month();
	int day_ = day();

	if(day_ > days_in_a_month(year_, month_)) {		
		day_ -= 1;
	}

	date2julian_day_number( year_, month_, day_);
	clear_cache();
}

}