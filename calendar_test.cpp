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
	Gregorian ten_days; ten_days += 10;
	if(related.add_related_event(ten_days, -2, "Ten days from today", "Ten minus two days from today")) {
		std::cout << "related.add_related_event(Gregorian() += 10, -2, \"Ten days from today\"";
		std::cout << ", \"Ten minus two days from today\")" << std::endl;
	}
	std::cout << "----------------------------------------" << std::endl;
	std::cout << related;
	std::cout << "----------------------------------------" << std::endl;

	Gregorian tmr; ++tmr;
	if(related.move_event(tday, tmr, "Today")) {
		std::cout << "related.move_event(Gregorian(), ++Gregorian(), \"Today\")" << std::endl;
	}
	std::cout << "----------------------------------------" << std::endl;
	std::cout << related;
	std::cout << "-----------Test move_event()------------" << std::endl;


	cal.set_format(Calendar<Gregorian>::list);
	std::cout << std::endl << "-------Test reccuring events------------" << std::endl;
	Calendar<Gregorian> recurring_cal;
	std::cout << "recurring_cal.add_yearly_event(Gregorian(2011,12,24), \"Christmas\", 4)" << std::endl;
	recurring_cal.add_yearly_event(Gregorian(2011,12,24), "Christmas", 4);
	std::cout << "recurring_cal.add_weekly(Gregorian(), \"Lab presentation\")" << std::endl;
	recurring_cal.add_weekly_event(Gregorian(), "Lab presentation");
	std::cout << "----------------------------------------" << std::endl;
	std::cout << recurring_cal;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "recurring_cal.remove_event(\"Christmas\", 2011,12,24)" << std::endl;
	recurring_cal.remove_event("Christmas", 2011,12,24);
	std::cout << "----------------------------------------" << std::endl;
	std::cout << recurring_cal;


	std::cout << std::endl << "--------Test birthdays--------------" << std::endl;
	
	std::cout << std::endl << "\t**** Extrauppgift 2.2 ****" << std::endl;
	cal.set_date(2000,12,2);

	cal.set_format(Calendar<Gregorian>::cal);
	std::cout << "----------------------------------------" << std::endl;
	std::cout << cal;
	
	cal.set_format(Calendar<Gregorian>::iCalendar);
	std::cout << "----------------------------------------" << std::endl;
	std::cout << cal;
	std::cout << "----------------------------------------" << std::endl;

	return 1;
};