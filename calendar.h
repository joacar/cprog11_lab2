#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <string>
#include <map>

#include "date.h"

namespace lab2 {

template<class T> 
class Calendar {
	private:
		//typedef typename std::pair<T, std::string> Event;
		//typedef std::map< Event > Events;
		//typedef typename std::map< T, std::string > Events;

		T date;
		std::map< T, std::string > events;

		T& set_default_date(int, int, int);

	public:
		Calendar();
		template<class U> Calendar (const Calendar<U>& cal);
		~Calendar();

		template<class U> T& operator=(const Calendar<U>& rhs);

		template<class U> friend std::ostream& operator<<(std::ostream& os, const Calendar<U>& cal);

		bool set_date(int, int, int);
		bool add_event(std::string event, int = -1, int = -1, int = -1);
		bool remove_event(std::string event, int = -1, int = -1, int = -1);
};

}
#endif