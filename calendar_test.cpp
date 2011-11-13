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

	cal.set_format(Calendar<Gregorian>::cal);
	std::cout << cal;

	cal.set_format(Calendar<Gregorian>::list);
	
	std::cout << "----------------------------------------" << std::endl;
	cal.remove_event("Vårdagjämning", 20, 3, 2000);
	cal.remove_event("Kalle Anka hälsar god jul", 24, 12, 2000);

	cal.set_date(2000, 11, 2);
	if (! cal.remove_event("Julafton", 24)) {
		std::cout << " cal.remove_event(\"Julafton\", 24) tar inte"; 
		std::cout << " bort något eftersom aktuell månad är november" << std::endl;
	}
	
	std::cout << "----------------------------------------" << std::endl;
	std::cout << cal;
	std::cout << "---------Test copy constructor----------" << std::endl;


	Calendar<Julian> jul_cal;
	jul_cal.set_date(2011,11,10);
	jul_cal.add_event("Idag klarade vi labben");
	jul_cal.add_event("Basketträning", 4, 12, 2011);
	jul_cal.add_event("Basketträning", 11, 12, 2011);
	jul_cal.add_event("Nyårsfrukost", 1, 1, 2012);
	Calendar<Gregorian> greg_cal(jul_cal);

	std::cout << greg_cal;
	std::cout << std::endl << "*** Extrauppgift 2.1 ***" << std::endl;
	std::cout << "-----------Test move_event()------------" << std::endl;
	std::cout << "Success: Test moving event from date that exists to non-existing date to" << std::endl;
	Gregorian greg1(2000,12,1);
	Gregorian greg2(2000,12,8);
	std::cout << "\t";
	if(cal.move_event(greg1, greg2, "Första advent") ) {
		std::cout << "successfully performed move_event( " << greg1 << ", " << greg2 << ", \"Första advent\")" << std::endl;
	}
	else {
		std::cout << "failed to perform move_event( " << greg1 << ", " << greg2 << ", \"Första advent\")" << std::endl;	
	}
	std::cout << "Fail: Test moving event that does not exist on date from to non-existing date to" << std::endl;
	Gregorian greg3(2011,10,10);
	std::cout << "\t";
	if(cal.move_event(greg1, greg3, "Första advent") ) {
		std::cout << "successfully performed move_event( " << greg1 << ", " << greg3 << ", \"Första advent\")" << std::endl;
	}
	else {
		std::cout << "failed to perform move_event( " << greg1 << ", " << greg3 << ", \"Första advent\")" << std::endl;	
	}
	std::cout << "Succes: Test moving event to a date with an existing event but not same date" << std::endl;
	Gregorian greg4(2000,12,25);
	std::cout << "\t";
	if(cal.move_event(greg2, greg3, "SANTA IS HERE!") ) {
		std::cout << "successfully performed move_event( " << greg2 << ", " << greg3 << ", \"SANTA IS HERE!\")" << std::endl;
	}
	else {
		std::cout << "failed to perform move_event( " << greg2 << ", " << greg3 << ", \"SANTA IS HERE!\")" << std::endl;	
	}

	std::cout << cal;

	cal.set_format(Calendar<Gregorian>::cal);

	std::cout << cal;

	cal.set_date(2011,12,1);

	cal.set_format(Calendar<Gregorian>::iCalendar);

	std::cout << cal;

	cal.set_format(Calendar<Gregorian>::list);
	std::cout << std::endl << "-------Test reccuring events------------" << std::endl;
	std::cout << "cal.add_recurring_events(\"Work\")" << std::endl;
	cal.add_recurring_events("Work");
	std::cout << cal;

	Calendar<Gregorian> x_mas;
	std::cout << "cal.add_recurring_events(\"Christmas\", greg(2011,12,24)";
	std::cout << " , 10, Calendar<Gregorian>::yearly)" << std::endl;
	Gregorian greg(2011,12,24);
	x_mas.add_recurring_events("Christmas", greg, 10, Calendar<Gregorian>::yearly);
	std::cout << x_mas;

	std::cout << std::endl << "--------Test birthdays--------------" << std::endl;
	std::cout << "Calendar<Gregorian> b_day" << std::endl;
	Calendar<Gregorian> b_day;
	std::cout << "add_birthday(\"Joakim\", 1988,7,20)" << std::endl;
	std::cout << "add_birthday(\"Pascal\", 1988,12,16)" << std::endl;

	b_day.add_birthday("Joakim", 1988,7,20);
	b_day.add_birthday("Pascal", 1988,12,16);	
	std::cout << "calculate_age(\"Joakim\")" << std::endl;
	b_day.calculate_age("Joakim");
	std::cout << "calculate_age(\"Pascal\")" << std::endl;
	b_day.calculate_age("Pascal");

	std::cout << "add_birthday(\"Leap day\", 2000,2,29)" << std::endl;
	b_day.add_birthday("Leap day", 2000,2,29);
	std::cout << "b_day.set_date(2001,2,28)" << std::endl;
	b_day.set_date(2001,2,28);
	std::cout << "calculate_age(\"Leap day\")" << std::endl;
	b_day.calculate_age("Leap day");
	std::cout << "b_day.set_date(2004,2,28)" << std::endl;
	b_day.set_date(2004,2,29);
	std::cout << "calculate_age(\"Leap day\")" << std::endl;
	b_day.calculate_age("Leap day");



	return 1;
}