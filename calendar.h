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
		T date;
		std::multimap<T, std::string> events;

		Calendar() : date(), events() {};
		template<class U> Calendar (const Calendar<U>& cal) : date( cal.date ), events() {
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

			typename std::multimap< U, std::string >::const_iterator it, end;
			end = rhs.events.end();

			for(it = rhs.events.begin(); it != end; it++) {
				events.insert( std::pair<T, std::string>(it->first, it->second) );
			}
			return *this;
		};

		friend std::ostream& operator<<(std::ostream& os, const Calendar<T>& cal) {
			typename std::multimap<T, std::string>::const_iterator it, end;
			end = cal.events.end();

			for(it = cal.events.begin(); it != end; it++) {
				if(it->first > cal.date)
					os << it->first << " : " << it->second << std::endl;	
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
};

}
#endif