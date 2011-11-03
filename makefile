%.out:	%.cpp
	g++ -m32 -g -Wall $*.cpp -o $*.out

# Change these
DATE 	= date.cpp westerndate.cpp
KATTIS 	= kattistime.cpp
GREGORIAN = gregorian.cpp
JULIAN = julian.cpp	
OBJ_ALL	= cprog09lab22c.cpp $(DATE) $(GREGORIAN) $(JULIAN) $(KATTIS)
OBJ_GREG = cprog09lab22b.cpp $(DATE) $(GREGORIAN) $(KATTIS)
OBJ_JULI = cprog09lab22a.cpp $(DATE) $(JULIAN) $(KATTIS)

datetest.out:
	echo Generates datetest.out ...
	g++ -g -Wall -o datetest.out datetest.cpp $(DATE) $(JULIAN) $(GREGORIAN) $(KATTIS) 

dates.out:
	echo Generates dates.out ...
	g++ -g -Wall -o dates.out dates.cpp $(DATE) $(GREGORIAN) $(JULIAN) $(KATTIS)

gregorian_tests:
	echo Generating Gregorian tests
	g++ -g -Wall -o gregorian_tests.out $(DATE) $(GREGORIAN) $(KATTIS)

julian_tests:
	echo Generating Julian tests
	g++ -g -Wall -o julian_tests.out $(DATE) $(JULIAN) $(KATTIS)
	cat oldkattis/lab22a.in | ./julian_tests.out > julian_tests.txt

gregorian_and_julian_tests:
	echo Generating Gregorian and Julian tests
	g++ -g -Wall -o gregorian_and_julian_tests.out $(OBJ_ALL)
	cat oldkattis/lab22c.in | ./gregorian_and_julian_tests.out > gregorian_and_julian_tests.txt

clean:
	rm -f *.o *.out testcode.cpp

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out
