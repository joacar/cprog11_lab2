#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

#include "calendar.h"
#include "date.h"

namespace lab2 {

template <class T>
Calendar<T>::Calendar() :
	date(),
	events() { }

template <class T>
template<class U> Calendar<T>::Calendar(const Calendar<U>& cal) :
	date( cal.date ),
	events() 
	{
		typename std::map< T, std::string>::iterator it;
		it = cal.events.begin();

		while(++it != cal.events.end()) {		// prefix or postfix?
			cal.events.insert( (*it) );
		}
	}

template <class T>
Calendar<T>::~Calendar() { }

template <class T>
template<class U> T& Calendar<T>::operator=(const Calendar<U>& rhs) { 
	if(*this != rhs) {
		date = rhs.date;

		typename std::map< T, std::string>::iterator it;
		it = rhs.events.begin();

		while(++it != rhs.events.end() ) {		// prefix or postfix?
			events.insert( (*it) );
		}
	}
	return *this;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Calendar<T>& cal) {
	typename std::map< T, std::string>::iterator it;
	it = cal.events.begin();

	while(++it != cal.events.end()) {
		os << it->first << " : " << it->second;	
	}
	return os;
}


template <class T>
T& Calendar<T>::set_default_date(int d, int m, int y) {
	if(y != -1) {
		return T(d, m, y );
	} 
	else if(m != -1) {
		return T(d, m, date.year() );
	}
	else if(d != -1) {
		return T(d, date.month(), date.month() );
	}

	return date;
}

template <class T>
bool Calendar<T>::set_date(int d, int m, int y) {
	try {
		date = T(d, m, y);
	} catch(std::out_of_range& e) {
		return false;
	}
	return true;
}

template <class T>
bool Calendar<T>::add_event(std::string event, int d, int m, int y) {
	try {
		T date_ = set_default_date(d, m, y);

		if(events.find(date_)) {	//TODO
			return false;
		}
		events.insert( Event(date_, event) );

	} catch(std::out_of_range& e) {
		return false;
	}
	return true;
}

template<class T>
bool Calendar<T>::remove_event(std::string event, int d, int m, int y) {
	try {
		T date_ = set_default_date(d, m, y);
		if(!events.find(date_)) {	// TODO
			return false;
		}
		events.remove( date_ );

	} catch (std::out_of_range& e) {
		return false;
	}
	return true;
}

}