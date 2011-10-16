#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Date
{
private:

	time_t date;

public:
	
	// Default constructor sets date to today
	Date() : date( time(&date) ) {}

	// Create a date object given a certain Unix time
	Date(time_t given_date) : date( given_date ) {}

	virtual ~Date() {}

	ostream & operator<<(ostream & os, const Date &) {
		local_time = localtime(&date);
		os << asctime(local_time);
		return os; 
	}
};

int main(){
	Date today = Date();
	cout << "Today's date is: " << today << endl;
	Date tomorrow = Date()
	return 0;
}