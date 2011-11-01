%.out:	%.cpp
	g++ -m32 -g -Wall $*.cpp -o $*.out

# Change these
cxxtestpath = ../../../cxxtest/
testcode    = test_vec.h
test_file	= vector.h
test_files	= dates.cpp Date.cpp WesternDate.cpp Gregorian.cpp Julian.cpp kattistime.cpp

datetest.out:
	echo Generates datetest.out ...
	g++ -g -Wall -o datetest.out datetest.cpp Date.cpp WesternDate.cpp Gregorian.cpp Julian.cpp kattistime.cpp

dates.out:
	echo Generates dates.out ...
	g++ -g -Wall -o dates.out dates.cpp Date.cpp WesternDate.cpp Gregorian.cpp Julian.cpp kattistime.cpp

gregorian_tests:
	echo Generating Gregorian tests
	g++ -g -Wall -o gregorian_tests.out cprog09lab22b.cpp Date.cpp WesternDate.cpp Gregorian.cpp kattistime.cpp

julian_tests:
	echo Generating Julian tests
	g++ -g -Wall -o julian_tests.out cprog09lab22a.cpp Date.cpp WesternDate.cpp Julian.cpp kattistime.cpp
	cat oldkattis/lab22a.in | ./julian_tests.out > julian_tests.txt

gregorian_and_julian_tests:
	echo Generating Gregorian and Julian tests
	g++ -g -Wall -o gregorian_and_julian_tests.out cprog09lab22c.cpp Date.cpp WesternDate.cpp Gregorian.cpp Julian.cpp kattistime.cpp
	cat oldkattis/lab22c.in | ./gregorian_and_julian_tests.out > gregorian_and_julian_tests.txt

clean:
	rm -f *.o *.out testcode.cpp

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out
