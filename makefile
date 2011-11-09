OBJECTS = date.o westerndate.o gregorian.o julian.o kattistime.o calendar.o

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

calendar_test: $(OBJECTS) calendar_test.o
	$(CXX) $(CFLAGS) $(OBJECTS) calendar_test.o -o calendar_test.out	

# Change these
DATE 	= date.cpp westerndate.cpp
KATTIS 	= kattistime.cpp
GREGORIAN = gregorian.cpp
JULIAN = julian.cpp
DATE_CONVERSIONS = date_conversions.cpp	

calendar_test.out:
	g++ -g -Wall -o calendar_test.out calendar_test.cpp $(DATE) $(JULIAN) $(GREGORIAN) $(KATTIS) calendar.cpp calendar.h

datetest.out:
	echo Generates datetest.out ...
	g++ -g -Wall -o datetest.out datetest.cpp $(DATE) $(JULIAN) $(GREGORIAN) $(KATTIS)

dates.out:
	echo Generates dates.out ...
	g++ -g -Wall -o dates.out dates.cpp $(DATE) $(GREGORIAN) $(JULIAN) $(KATTIS)

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

calendar_tests:
	g++ -g -Wall -o calendar_tests.out cprog09lab23.cpp $(DATE) $(JULIAN) $(KATTIS) calendar.cpp
	cat oldkattis/lab23.in | ./calendar_tests.out > results/calendar_tests.txt
	
clean:
	rm -f *.o *.out testcode.cpp

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out
