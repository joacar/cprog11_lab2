#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <set>
#include <stdexcept>

namespace lab2 {

template<class T> 
class Calendar {
public:
	struct Event {
		T date;
		std::string name;
		std::set< std::pair<T, std::string> > related;
		bool is_birthday, is_child;
		std::pair<T, std::string> parent;

		Event(T d, std::string n, bool b_day = false) :
			date(d), name(n), related(), is_birthday(b_day), is_child(false), parent() {};
		
		Event(T d, std::string n, const Event& rel, bool b_day = false) :
			date(d), 
			name(n), 
			related(), 
			is_birthday(b_day),
			is_child(true),
			parent(std::make_pair<T, std::string>(rel.date,rel.name)) {};

		friend std::ostream& operator<<(std::ostream& os, const Event& e) {
			os << e.name;

			if(e.is_child)
				os << " has parent " << e.parent.first << " : " << e.parent.second; 
			if(e.related.size() > 0)
				os << " and " << e.related.size() << " related event(s)";

			return os;
		};		
	};

	typedef typename std::multimap<T, Calendar<T>::Event>::const_iterator const_iterator_t;
	typedef typename std::multimap<T, Calendar<T>::Event>::iterator iterator_t;
	typedef std::multimap<T, Calendar<T>::Event> event_t;

	T set_default_date(int d, int m, int y) {
		int year, month, day;
		year = (y == -1) ? date.year() : y;
		month = (m == -1) ? date.month() : m;
		day = (d == -1) ? date.day() : d;
		
		return T(year,month,day);
	};

	bool add_event(const Event& e) {
		iterator_t first = events.lower_bound(e.date), last = events.upper_bound(e.date);
		for(iterator_t it = first; it != last; it++) {
			if(it->first == e.date && it->second.name == e.name)
				return false;
		}
		events.insert( std::make_pair(e.date, e) );
		return true;
	};

	bool remove_event(const Event& e) {
		iterator_t first = events.lower_bound(e.date), last = events.upper_bound(e.date);
		for(iterator_t it = first; it != last; it++) {
			Event& event = it->second;
			if(event.date == e.date && event.name == e.name) {
				if(event.is_child)
					remove_relation(event);
				
				typename std::set< std::pair<T, std::string> >::iterator rel;
				for(rel = event.related.begin(); rel != event.related.end(); rel++)
					remove_event( Event(rel->first, rel->second) );
				
				events.erase(it);
				return true;
			}
		}
		return false;
	};

	void remove_relation(Event& e) {
		for(iterator_t it = events.lower_bound(e.date); it != events.upper_bound(e.date); it++) {
			Event& parent = it->second;
			if(parent.name == e.name) {
				parent.related.erase(std::make_pair<T, std::string>(e.date, e.name) );
				return;
			}
		}
	};

	//public:
		enum format {list, cal, iCalendar};
		
		T date;
		std::multimap<T, Calendar<T>::Event> events, b_days;
		format print_format;

		Calendar() : date(), events(), b_days(), print_format(list) {};
		
		template<class U> Calendar(const Calendar<U>& cal) : 
			date(cal.date), 
			events(), 
			b_days(),
			print_format(list) // TODO -> cant assigne const <U> cal format
			{
				typename std::multimap<U, Event>::const_iterator it;
				//for(it = cal.events.begin(); it != cal.events.end(); it++)
				//	events.insert( std::pair<U, Event>(it->first, it->second) );
		};

		~Calendar() {};

		template<class U> Calendar& operator=(const Calendar<U>& rhs) {
			date = rhs.date;
			events.clear();
			print_format = rhs.print_format;
			b_days.clear();

			typename std::multimap<U, Event>::const_iterator it;
			for(it = rhs.events.begin(); it != rhs.events.end(); it++)
				events.insert( std::pair<U, Event>(it->first, it->second) );
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

		bool add_event(std::string e, int d = -1, int m = -1, int y = -1) {
			try {
				return add_event( Event( set_default_date(d,m,y), e) );
			} catch(std::out_of_range& e) {
				return false;
			}
		};

		bool remove_event(std::string e, int d = -1, int m = -1, int y = -1) {
			try {
				return remove_event( Event( set_default_date(d,m,y), e) );
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
			int diff = to - from;
			for(iterator_t it = events.begin(); it != events.end(); it++) {
				//std::cout << "\tEvent: " << it->second.name << " input: " << event << std::endl;
				if(it->first == from && it->second.name == event) {
					Event& e = it->second;
					//std::cout << "\t\tEvent: " << e << std::endl;
					//if(!add_event(e)) return false;

					if(e.is_child) {
						e.parent.first += diff; // update parent
						iterator_t first = events.lower_bound(e.date), second = events.upper_bound(e.date);
						for(iterator_t it = first; it != second; it++) {
							if(it->second.date == e.parent.first && it->second.name == e.parent.second) {
								Event& parent = it->second;
								

							}
						}
					}
					
					typename std::set< std::pair<T, std::string> >::iterator rel;
					for(rel = e.related.begin(); rel != e.related.end(); rel++) {
						T new_date(rel->first);
						new_date += diff;
						move_event(rel->first, new_date, rel->second);
					}

					Event tmp = e;
					events.erase(it);
					tmp.date = to;
					events.insert( std::pair<T, Event>(to, tmp) );
					return true;
				}
			}
			return false;
		};

		bool add_related_event(const Date& rel_date, int days, std::string rel_event, std::string new_event) {
			iterator_t first = events.lower_bound(rel_date), end = events.upper_bound(rel_date);

			for(iterator_t it = first; it != end; it++) {
				Event& rel_e = it->second;
				if(rel_e.name == rel_event) {	// rel_date found
					T new_date(rel_date);
					new_date += days;
					Event new_e(new_date, new_event, rel_e);

					if(!add_event(new_e)) return false;

					rel_e.related.insert( std::pair<T, std::string>(new_date, new_event) );
					return true;
				}
			}
			return false;	// rel_date not found
		};

		bool add_recurring_events(std::string e, int y=-1, int m = -1, int d = -1, int repeat = 100, interval_t interval = daily) {
			return recurring_events(e, &Calendar<T>::add_event, y, m, d, repeat, interval);	
		};

		bool remove_recurring_events(std::string e, int y=-1, int m = -1, int d = -1, int repeat = 100, interval_t interval = daily) {
			return recurring_events(e, &Calendar<T>::remove_event, y, m, d, repeat, interval);
		};

		bool add_birthday(std::string name, int y, int m, int d) {
			return recurring_events(name, &Calendar<T>::add_event,y, m, d, 50, Calendar<T>::yearly);
		};

		bool recurring_events(std::string e, bool (Calendar<T>::*operation)(const Event&),
						int y = -1, int m = -1, int d = -1, int repeat = 100, interval_t interval = daily) {
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
					(*this.*operation)( Event(date_, e) );
				}
			} catch(std::out_of_range) {
				return false;
			}
			return true;
		};


		bool calculate_age(std::string name) const {
			const_iterator_t it, end;

			end = b_days.end();
			for(it = b_days.begin(); it != end; it++) {
				if(it->second.name == name) {
					int y = date.year() - (it->first).year();
					int m = date.month() - (it->first).month();
					int d = date.day() - (it->first).day();
					// this is not a very generic solution ... if it is leap year this should not be exe.
					if( date.month() == 2 && (it->first).days_this_month() == 29 
							&& d == 0) {
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
			const_iterator_t it, end;

			for(it = events.begin(); it != events.end(); it++) {
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
				if(i < first_week_day_this_month || i > days_this_month_ + first_week_day_this_month-1) {
					os << "    ";
				}
				else {
					//std::cout << "i: " << i << std::endl;
					// if current date equals cal date surround with < >
					int day_ = date_.day();	
					if(day_ == date.day()) {
						os << "<"; if(day_ < 10) os << " "; os << day_ << ">";
					} else {
						os << " "; if(day_ < 10) os << " "; os << day_;
						// if date has an event add * after else add padding
						// TODO -> below doesn't work...
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

			for(const_iterator_t it = events.begin(); it != events.end(); it++) {
				if((*it).year == date.year() && (*it).first.month() == date.month())
					os << (*it).first << ": " << (*it).second << std::endl;
			}
			return os;
		}

		std::ostream& print_iCalendar_format(std::ostream& os) const {
			os << "BEGIN:" << "VCALENDAR" << std::endl;
			os << "VERSION:" << 2.0 << std::endl;
			os << "PRODID:" << "//SUCCESSFULLY DEFETED KATTIS!" << std::endl;
			const_iterator_t it, end;
			end = events.end();
			for(it = events.begin(); it != end; it++) {
				os << "BEGIN:" << "VEVENT" << std::endl;
				os << "DTSTART:" << it->first.year();
				if( it->first.month() < 10 )  os << "0"; os << it->first.month();
				if(it->first.day() < 10 ) os << "0"; os << it->first.day() << "T080000" << std::endl;
				os << "DTEND:" << it->first.year();
				if(it->first.month() < 10 ) os << "0"; os << it->first.month();
				if(it->first.day() < 10 ) os << "0"; os << it->first.day() << "T090000" << std::endl;
				os << "SUMMARY:" << it->second << std::endl;
				os << "END:" << "VEVENT" << std::endl;
			}
			os << "END:" << "VCALENDAR" << std::endl;

			return os;
		};

};

}
#endif