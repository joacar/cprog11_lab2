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
	// fails
	T& set_default_date(int d, int m, int y) {
		T date_;
		if(y != -1) {
			return date_(d, m, y );
		} 
		else if(m != -1) {
			return date_(d, m, date.year() );
		}
		else if(d != -1) {
			return date_(d, date.month(), date.month() );
		}
		else {
			return date;
		}
	};

	public:
		enum format {list, cal, iCalendar};

		T date;
		std::multimap<T, std::string> events;
		format print_format;

		Calendar() : date(), events(), print_format( list ) {};
		
		template<class U> Calendar(const Calendar<U>& cal) : 
			date( cal.date ), 
			events(), 
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

		bool add_event(std::string e) {
			return add_event(e, date.day(), date.month(), date.year());
		}
		
		bool add_event(std::string e, int d) { 
			return add_event(e, d, date.month(), date.year());
		};
		
		bool add_event(std::string e, int d, int m) {
			return add_event(e, d, m, date.year()); 
		};
		
		bool add_event(std::string event, int d, int m, int y) {
			try {
				T date_ = T(y, m, d);

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

		bool remove_event(std::string e) {
			return remove_event(e, date.day(), date.month(), date.year());
		}

		bool remove_event(std::string e, int d) { 
			return remove_event(e, d, date.month(), date.year());
		};
		
		bool remove_event(std::string e, int d, int m) {
			return remove_event(e, d, m, date.year()); 
		};

		bool remove_event(std::string event, int d, int m, int y) {
			try {
				T date_ = T(y, m, d);
				
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

		void add_repeated_events(const Date& date, std::string event, int repeat = 100) {
			
		};

		void add_birthday(const Date& date, std::string name, std::string message) {
			
		};

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
					if(date_ == date) {
						os << "<"; if(i < 10) os << " "; os << i << ">";
					} else {
						os << " "; if(i < 10) os << " "; os << i;
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
			os << std::endl << std::endl;
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