#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <set>
#include <stdexcept>

namespace lab2 {

template<class T> 
class Calendar {
	private:
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
				os << e.name; // os << e.date << " : " << e.name;

				if(e.is_birthday) {
					int year = e.date.year()  - e.parent.first.year();
					os << " is " << year << "year(s) old";
				}

				// if(e.is_child)
				// 	os << " has parent " << e.parent.first << " : " << e.parent.second; 
				// if(e.related.size() > 0)
				// 	os << " has " << e.related.size() << " related event(s)";

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
			iterator_t it = events.lower_bound(e.date);// last = events.upper_bound(e.date);
			for(; it != events.end(); ++it) {
				Event& event = it->second;
				if(event.date == e.date && event.name == e.name) {
					if(event.is_child)
						remove_relation(event);
					
					typename std::set< std::pair<T, std::string> >::iterator rel;
					for(rel = event.related.begin(); rel != event.related.end(); ++rel)
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
					parent.related.erase(std::make_pair(e.date, e.name) );
					break;
				}
			}
		};
		enum interval_t {daily, weekly, monthly, yearly};

		bool recurring_events(const Date& d, std::string s, int r, interval_t interval, bool bday=false) {
			try {
				if( !add_event( Event(d, s, bday) )) return false;

				T date(d);
				bool status = true;
				if(bday) {
					int padding_years = this->date.year() - d.year() - 1;
					date.add_year(padding_years);
				}
				for(int i = 0; i < r; ++i) {
					switch (interval) {
						case daily:
							++date;
							break;
						case weekly:
							date += date.days_per_week();
							break;
						case monthly:
							date.add_month();
							break;
						case yearly:
							date.add_year();
							break;
					}
					if( !add_related_event(d, date - d, s, s, bday) )
						status = false; 
				}
				return status;
			} catch(std::out_of_range) {
				return false;
			}
		};

		struct PrintListObject {
			void operator()(std::pair<T, Event> pair) const {
				std::cout << pair.first << " : " << pair.second << std::endl;
			};
		} print_list;
		

		void print_list_format() const {
			for_each(events.lower_bound(date), events.end(), print_list);
		};

		struct PrintiCalendarObject {
			void operator()(std::pair<T, Event> pair) {
				std::cout << "BEGIN:VEVENT" << std::endl;
				std::cout << "DTSTART:" << pair.first.year();
				if(pair.first.month() < 10)  std::cout << "0"; std::cout << pair.first.month();
				if(pair.first.day() < 10 ) std::cout << "0"; std::cout << pair.first.day() << "T080000" << std::endl;
				std::cout << "DTEND:" << pair.first.year();
				if(pair.first.month() < 10 ) std::cout << "0"; std::cout << pair.first.month();
				if(pair.first.day() < 10 ) std::cout << "0"; std::cout << pair.first.day() << "T090000" << std::endl;
				std::cout << "SUMMARY:" << pair.second << std::endl;
				std::cout << "END:VEVENT" << std::endl;
			}
		} print_iCalendar;

		std::ostream& print_iCalendar_format(std::ostream& os) const {
			os << "BEGIN:" << "VCALENDAR" << std::endl;
			os << "VERSION:" << 2.0 << std::endl;
			os << "PRODID:" << "//SUCCESSFULLY DEFETED KATTIS!" << std::endl;
			for_each(events.begin(), events.end(), print_iCalendar);
			os << "END:" << "VCALENDAR" << std::endl;

			return os;
		};

		std::ostream& print_cal_format(std::ostream& os) const {
			T date_ = T(date.year(), date.month(), 1);
			int days_per_week_ = date_.days_per_week();
			int days_this_month_ = date_.days_this_month();
			int start_of_month = date_.week_day();
			int end_of_month = days_this_month_ + start_of_month - 1;

			os << "\t" << date.month_name() << " " << date.year() << std::endl;
			os << " må  ti  on  to  fr  lö  sö " << std::endl;
			for(int i = 1; i <= days_per_week_*6; i++) {
				if(i % days_per_week_ == 1 && i != 1)
					os << std::endl;
				// for days not in month fill with spaces x 4
				if(i < start_of_month || i > end_of_month) {
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
			print_list_format();
			return os;
		}
	
	public:
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
					calendar.print_list_format();
					break;
				case cal:
					return calendar.print_cal_format(os);
				case iCalendar:
					return calendar.print_iCalendar_format(os);
			}
			return os;
		};

		/**************
		*** Methods ***
		***************/
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
				T date = set_default_date(d,m,y);
				return remove_event( Event( date, e) );
			} catch (std::out_of_range& e) {
				return false;
			}
		};

		bool move_event(const Date& from, const Date& to, std::string event) {
			return move_event(from, to, event, date, false);
		}

		bool add_related_event(const Date& rel_date, int days, std::string rel_event, std::string new_event,
								bool bday = false) {
			iterator_t first = events.lower_bound(rel_date), end = events.upper_bound(rel_date);
			for(; first != end; first++) {
				Event& rel_e = first->second;
				if(rel_e.name == rel_event) {	// rel_date found
					T new_date(rel_date);
					new_date += days;
					Event new_e(new_date, new_event, rel_e, bday);

					if(!add_event(new_e)) return false;

					rel_e.related.insert( std::make_pair(new_date, new_event) );
					return true;
				}
			}
			return false;	// rel_date not found
		};

		bool add_yearly_event(const Date& d, std::string e, int r = 100) {
			return recurring_events(d,e,r, Calendar<T>::yearly);
		};

		bool add_monthly_event(const Date& d, std::string e, int r = 100) {
			return recurring_events(d,e,r, Calendar<T>::monthly);
		};

		bool add_weekly_event(const Date& d, std::string e, int r = 100) {
			return recurring_events(d,e,r, Calendar<T>::weekly);
		};

		bool add_daily_event(const Date& d, std::string e, int r = 100) {
			return recurring_events(d,e,r, Calendar<T>::monthly);
		};

		bool add_birthday(const Date& d, std::string n, int r = 100) {
			return recurring_events(d,n,r,Calendar<T>::yearly, true);
		};

		void set_format(format print_format) { this->print_format = print_format; };
};

}
#endif