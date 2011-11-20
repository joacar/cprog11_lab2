#include "calendar.h"
#include "gregorian.h"
#include "julian.h"
#include "kattistime.h"

#include <iostream>
#include <time.h>

int main() {
	using namespace lab2;
	
	time_t time_now;
	time(&time_now);
	set_k_time(time_now);

	std::cout << "----------------------------------------" << std::endl;
	
	Calendar<Gregorian> cal;
	cal.set_date(2000, 12, 2);
	cal.add_event("Basketträning", 4, 12, 2000);
	cal.add_event("Basketträning", 11, 12, 2000);
	cal.add_event("Nyårsfrukost", 1, 1, 2001);
	cal.add_event("Första advent", 1); // år = 2000, månad = 12
	cal.add_event("Vårdagjämning", 20, 3); // år = 2000
	cal.add_event("Julafton", 24, 12);
	cal.add_event("Kalle Anka hälsar god jul", 24); // också på julafton
	cal.add_event("Julafton", 24); // En likadan händelse samma datum ska ignoreras och inte sättas in i kalendern
	cal.add_event("Min första cykel", 20, 12, 2000);
	cal.remove_event("Basketträning", 4);
	std::cout << cal; // OBS! Vårdagjämning och första advent är före nuvarande datum och skrivs inte ut
	
	std::cout << "----------------------------------------" << std::endl;
	cal.remove_event("Vårdagjämning", 20, 3, 2000);
	cal.remove_event("Kalle Anka hälsar god jul", 24, 12, 2000);

	cal.set_date(2000, 11, 2);
	if (! cal.remove_event("Julafton", 24)) {
		std::cout << " cal.remove_event(\"Julafton\", 24) tar inte" << std::endl; 
		std::cout << " bort något eftersom aktuell månad är november" << std::endl;
	}
	
	std::cout << "----------------------------------------" << std::endl;
	std::cout << cal;
	std::cout << std::endl << "---------Test copy constructor----------" << std::endl;
	Calendar<Julian> jul_cal;
	jul_cal.add_event("Hacking the db");
	jul_cal.add_event("Basketträning");
	jul_cal.add_event("Gymnastik");
	Calendar<Gregorian> greg_cal(jul_cal);

	std::cout << "Calendar<Julian> jul_cal;" << std::endl;
	std::cout << "jul_cal.add_event(\"Hacking the db\");" << std::endl;
	std::cout << "jul_cal.add_event(\"Basketträning\");;" << std::endl;
	std::cout << "jul_cal.add_event(\"Gymnastik\");" << std::endl;
	std::cout << "Calendar<Gregorian> greg_cal(jul_cal);" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << greg_cal;
	
	std::cout << std::endl << "\t*** Extrauppgift 2.1 ***" << std::endl;
	std::cout << "-----------Test related events----------" << std::endl;
	Calendar<Gregorian> related;
	Gregorian tday;
	if(related.add_event("Today")) std::cout << "related.add_event(\"Today\")" << std::endl;
	if(related.add_related_event(tday, 10, "Today", "Ten days from today")) {
		std::cout << "related.add_related_event(Gregorian(), 10, \"Today\", \"Ten days from today\")" << std::endl;
	}
	std::cout << "----------------------------------------" << std::endl;
	std::cout << related;
	std::cout << "----------------------------------------" << std::endl;

	Gregorian tmr; ++tmr;
	if(related.move_event(tday, tmr, "Today")) {
		std::cout << "related.move_event(\"Today\", Gregorian(), ++Gregorian())" << std::endl;
	}
	std::cout << "----------------------------------------" << std::endl;
	std::cout << related;

	std::cout << "-----------Test move_event()------------" << std::endl;


	cal.set_format(Calendar<Gregorian>::list);
	std::cout << std::endl << "-------Test reccuring events------------" << std::endl;
	//std::cout << "cal.add_recurring_events(\"Work\")" << std::endl;
	//cal.add_recurring_events("Work",);
	//std::cout << cal;

	Calendar<Gregorian> x_mas;
	std::cout << "cal.add_recurring_events(\"Christmas\", 2011,12,24";
	std::cout << " , 4, Calendar<Gregorian>::yearly)" << std::endl;
	x_mas.add_recurring_events("Christmas", 2011,12,24, 4, Calendar<Gregorian>::yearly);
	std::cout << "----------------------------------------" << std::endl;
	std::cout << x_mas;
	std::cout << "----------------------------------------" << std::endl;

	std::cout << "cal.remove_recurring_events(\"Christmas\", 2011,12,24";
	std::cout << " , 4, Calendar<Gregorian>::yearly)" << std::endl;
	x_mas.remove_recurring_events("Christmas", 2011,12,24, 4, Calendar<Gregorian>::yearly);
	std::cout << "----------------------------------------" << std::endl;
	std::cout << x_mas;


	std::cout << std::endl << "--------Test birthdays--------------" << std::endl;
	std::cout << "Calendar<Gregorian> b_day" << std::endl;
	Calendar<Gregorian> b_day;
	std::cout << "add_birthday(\"Joakim\", 1988,7,20)" << std::endl;
	std::cout << "add_birthday(\"Pascal\", 1988,12,16)" << std::endl;

	b_day.add_birthday("Joakim", 1988,7,20);
	b_day.add_birthday("Pascal", 1988,12,16);	

	std::cout << std::endl << "\t**** Extrauppgift 2.2 ****" << std::endl;
	cal.set_date(2011,12,1);

	cal.set_format(Calendar<Gregorian>::cal);
	std::cout << "----------------------------------------" << std::endl;
	std::cout << cal;
	
	cal.set_format(Calendar<Gregorian>::iCalendar);
	std::cout << "----------------------------------------" << std::endl;
	std::cout << cal;
	std::cout << "----------------------------------------" << std::endl;

	return 1;
};