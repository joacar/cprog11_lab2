%.out:	%.cpp
	g++ -m32 -g -Wall $*.cpp -o $*.out

# Change these
cxxtestpath = ../../../cxxtest/
testcode    = test_vec.h
test_file	= vector.h
test_files	= dates.cpp Date.cpp WesternDate.cpp Gregorian.cpp Julian.cpp kattistime.cpp

datetest.out:
	echo Generates test.out ...
	g++ -g -Wall -o datetest.out datetest.cpp Date.cpp WesternDate.cpp Gregorian.cpp Julian.cpp kattistime.cpp

gregorian_tests.out:
	echo Generating Gregorian tests
	g++ -g -Wall -o gregorian_tests.out cprog09lab22b.cpp Date.cpp WesternDate.cpp Gregorian.cpp kattistime.cpp

clean:
	rm -f *.o *.out testcode.cpp

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out
