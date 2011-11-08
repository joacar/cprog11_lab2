OBJECTS = date.o westerndate.o gregorian.o julian.o kattistime.o

CFLAGS += -g -Wall -Wextra -Weffc++ -O2

all:

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

# Header dependencies
date.o: date.h kattistime.h
westerndate.o: date.h westerndate.h
gregorian.o: date.h westerndate.h gregorian.h
julian.o: date.h westerndate.h julian.h
tests.o: date.h westerndate.h gregorian.h julian.§h
calendar.o: date.h calendar.h
calendar_test.o: date.h calendar.h
cprog09lab22a.o: date.h julian.h
cprog09lab22b.o: date.h gregorian.h
cprog09lab22c.o: date.h julian.h gregorian.h
cprog09lab23.o: calendar.h date.h

test: $(OBJECTS) tests.o
	$(CXX) $(CFLAGS) $(OBJECTS) tests.o -o tests

datetest: $(OBJECTS) datetest.o
	$(CXX) $(CFLAGS) $(OBJECTS) datetest.o -o datetest

# Change these
DATE 	= date.cpp westerndate.cpp
KATTIS 	= kattistime.cpp
GREGORIAN = gregorian.cpp
JULIAN = julian.cpp
DATE_CONVERSIONS = date_conversions.cpp	

datetest.out:
	echo Generates datetest.out ...
	g++ -g -Wall -o datetest.out datetest.cpp $(DATE) $(JULIAN) $(GREGORIAN) $(KATTIS) $(DATE_CONVERSIONS)

dates.out:
	echo Generates dates.out ...
	g++ -g -Wall -o dates.out dates.cpp $(DATE) $(GREGORIAN) $(JULIAN) $(KATTIS) $(DATE_CONVERSIONS)

gregorian_tests:
	echo Generating Gregorian tests
	g++ -g -Wall -o gregorian_tests.out cprog09lab22b.cpp $(DATE) $(GREGORIAN) $(KATTIS) $(DATE_CONVERSIONS)

julian_tests:
	echo Generating Julian tests
	g++ -g -Wall -o julian_tests.out cprog09lab22a.cpp $(DATE) $(JULIAN) $(KATTIS) $(DATE_CONVERSIONS)
	cat oldkattis/lab22a.in | ./julian_tests.out > results/julian_tests.txt

gregorian_and_julian_tests:
	echo Generating Gregorian and Julian tests
	g++ -g -Wall -o gregorian_and_julian_tests.out cprog09lab22c.cpp $(DATE) $(KATTIS) $(GREGORIAN) $(JULIAN) $(DATE_CONVERSIONS)
	cat oldkattis/lab22c.in | ./gregorian_and_julian_tests.out > results/gregorian_and_julian_tests.txt

clean:
	rm -f *.o *.out testcode.cpp

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out
