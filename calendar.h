#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <stdexcept>

namespace lab2 {

template<class T> 
class Calendar {
	T set_default_date(int d, int m, int y) {
		int year, month, day;
		year = (y == -1) ? date.year() : y;
		month = (m == -1) ? date.month() : m;
		day = (d == -1) ? date.day() : d;
		
		return T(year,month,day);

	};

	public:
		enum format {list, cal, iCalendar};
		
		T date;
		std::multimap<T, std::string> events, b_days;
		format print_format;

		Calendar() : date(), events(), b_days(), print_format( list ) {};
		
		template<class U> Calendar(const Calendar<U>& cal) : 
			date( cal.date ), 
			events(), 
			b_days(),
			print_format( list ) // TODO -> can assigne const <U> cal format
			{
				typename std::multimap< U, std::string >::const_iterator it, end;
				end = cal.events.end();

				for(it = cal.events.begin(); it != end; it++) {
					events.insert( std::pair<U, std::string>(it->first, it->second) );
				}
			};
		~Calendar() {};

		template<class U> Calendar& operator=(const Calendar<U>& rhs) {
			date = rhs.date;
			events.clear();
			print_format = rhs.print_format;

			typename std::multimap< U, std::string >::const_iterator it, end;
			end = rhs.events.end();

			for(it = rhs.events.begin(); it != end; it++) {
				events.insert( std::pair<T, std::string>(it->first, it->second) );
			}
			return *this;
		};

		friend std::ostream& operator<<(std::ostream& os, const Calendar<T>& calendar) {
			switch(calendar.print_format) {
				case list:
					return calendar.print_list_format(os);
				case cal:
					return calendar.print_cal_format(os);
				case iCalendar:
					return calendar.print_iCalendar_format(os);
			}
			return os;
		};

		bool set_date(int y, int m, int d) {
			try {
				date = T(y, m, d);
			} catch(std::out_of_range& e) {
				return false;
			}
			return true;
		};

		bool add_event(std::string event, int d = -1, int m = -1, int y = -1) {
			try {
				T date_ = set_default_date(d,m,y);//T(y, m, d);

				typename std::multimap<T, std::string>::iterator it, end;
				end = events.end();
				for(it = events.begin(); it != end; it++) {
					if(it->first == date_ && it->second == event)
						return false;
				}
				events.insert( std::pair<T, std::string>(date_, event) );
				return true;
			} catch(std::out_of_range& e) {
				return false;
			}
		};

		bool remove_event(std::string event, int d = -1, int m = -1, int y = -1) {
			try {
				T date_ = set_default_date(d,m,y);
				
				typename std::multimap<T, std::string>::iterator it, end;
				end = events.end();
				for(it = events.begin(); it != end; it++) {
					if(it->first == date_ && it->second == event) {
						events.erase(it);
						return true;
					}
				}
				return false;
			} catch (std::out_of_range& e) {
				return false;
			}
		};

		/***********************
		**** Extrauppgift 2.1 **
		************************/
		enum interval_t {daily, weekly, monthly, yearly};
		// not very generic
		enum week_days_t {monday = 1, tuesday, wednesday, thursday, friday, saturday, sunday};

		bool move_event(const Date& from, const Date& to, std::string event) {
			typename std::multimap<T, std::string>::iterator it, end;
			
			end = events.end();
			for(it = events.begin(); it != end; it++) {
				if(it->first == from && it->second == event) {
					bool success = add_event(event, to.day(), to.month(), to.year());
					if(success)		// remove event only if it is successfully added
						events.erase(it);
					return success;
				}
			}
			return false;
		};

		bool add_related_event(const Date& rel_date, int days, std::string rel_event, std::string new_event) {
			return true;	
		};
		
		bool add_recurring_events(std::string event, int y = -1, int m = -1, int d = -1, int repeat = 100, interval_t interval = daily) {
			int y_, m_, d_;

			try {
				T date_ = set_default_date(d,m,y);
			
				for(int i = 0; i < repeat; i++) {
					switch (interval) {
						case daily:
							++date_;
							break;
						case weekly:
							date_ += date_.days_per_week();
							break;
						case monthly:
							date_.add_month();
							break;
						case yearly:
							date_.add_year();
							break;
					}
					y_ = date_.year();
					m_ = date_.month();
					d_ = date_.day();
					add_event(event,d_,m_,y_);
				}
			} catch(std::out_of_range) {
				return false;
			}
			return true;
		};

		bool add_birthday(std::string name, int y, int m, int d) {
			try {
				T date_ = T(y,m,d);

				typename std::multimap<T, std::string>::iterator it, end;
				end = b_days.end();
				for(it = b_days.begin(); it != end; it++) {
					if(it->first == date_ && it->second	== name)
						return false;
				}
				b_days.insert(std::pair<T, std::string>(date_, name));
				return true;
			}catch(std::out_of_range& e) {
					return false;
			}
		};

		bool calculate_age(std::string name) const {
			typename std::multimap<T, std::string>::const_iterator it, end;
			int y = 0,m = 0,d = 0;

			end = b_days.end();
			for(it = b_days.begin(); it != end; it++) {
				if(it->second == name) {
					y = date.year() - (it->first).year();
					m = date.month() - (it->first).month();
					d = date.day() - (it->first).day();
					// this is not a very generic solution ... if it is leap year this should not be exe.
					if( date.month() == 2 && (it->first).days_this_month() == 29) {
						d += 1;	
					}
					if(d < 0) {
						m--;
						d += date.days_this_month();
							
					}
					if(m < 0) {
						y--;
						m += date.months_per_year();
					}
					std::cout << "Age of " << name << " is " << y << " years, " << m << " months and " << d << " days" << std::endl;
					return true;
				}
			}
			return false;
		}

		/***********************
		*** Extrauppgift 2.2 ***
		************************/		
		void set_format(format print_format) {
			this->print_format = print_format;
		}

		std::ostream& print_list_format(std::ostream& os) const {
			typename std::multimap<T, std::string>::const_iterator it, end;
			end = events.end();

			for(it = events.begin(); it != end; it++) {
				if(it->first > date)
					os << it->first << " : " << it->second << std::endl;	
			}
			return os;	
		};

		std::ostream& print_cal_format(std::ostream& os) const {
			T date_ = T(date.year(), date.month(), 1);
			int days_per_week_ = date_.days_per_week();
			int days_this_month_ = date_.days_this_month();
			int first_week_day_this_month = date_.week_day();

			os << "\t" << date_.month_name() << " " << date_.year() << std::endl;
			os << " må  ti  on  to  fr  lö  sö " << std::endl;
			for(int i = 1; i <= days_per_week_*6; i++) {
				if(i % days_per_week_ == 1 && i != 1)
					os << std::endl;
				// for days not in month fill with spaces x 4
				if(i < first_week_day_this_month || i > days_this_month_) {
					os << "    ";
				}
				else {
					// if current date equals cal date surround with < >
					int day_ = date_.day();	
					if(day_ == date.day()) {
						os << "<"; if(day_ < 10) os << " "; os << day_ << ">";
					} else {
						os << " "; if(day_ < 10) os << " "; os << day_;
						// if date has an event add * after else add padding
						if(events.find(date_) != events.end()) {
							os << "*";
						} else {
							os << " ";
						}
					}
					++date_;
				}
			}
			os << std::endl;
			typename std::map<T, std::string>::const_iterator it, end;
			end = events.end();

			for(it = events.begin(); it != end; it++) {
				if((*it).first.month() == date.month())
					os << (*it).first << ": " << (*it).second << std::endl;
			}
			os << std::endl;
			return os;
		}

		std::ostream& print_iCalendar_format(std::ostream& os) const {
			os << "BEGIN:" << "VCALENDAR" << std::endl;
			os << "VERSION:" << 2.0 << std::endl;
			os << "PRODID:" << "//SUCCESSFULLY DEFETED KATTIS!" << std::endl;
			typename std::map<T, std::string>::const_iterator it, end;
			end = events.end();
			for(it = events.begin(); it != end; it++) {
				os << "BEGIN:" << "VEVENT" << std::endl;
				os << "DTSTART:" << it->first.year() << it->first.month() << it->first.day() << "T080000" << std::endl;
				os << "DTEND:" << it->first.year() << it->first.month() << it->first.day() << "T090000" << std::endl;
				os << "SUMMARY:" << it->second << std::endl;
				os << "END:" << "VEVENT" << std::endl;
			}
			os << "END:" << "VCALENDAR" << std::endl;

			return os;
		};

};

}
#endif