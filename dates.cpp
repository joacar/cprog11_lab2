#include <iostream>
#include <time.h>

#include "gregorian.h"
#include "julian.h"
#include "kattistime.h"

using namespace lab2;
using namespace std;

int main(){
	// Set kattistime to right now
	time_t time_now;
	time(&time_now);
	set_k_time(time_now);

	const Julian& j = new Julian(2319,1,7);
	const Gregorian& g = Gregorian(j);
	const Gregorian& g2 = Gregorian(g);
	const Julian& j2 = Gregorian(g2);
	cout << j2 << endl;

	return 0;
}