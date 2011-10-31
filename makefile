%.out:	%.cpp
	g++ -m32 -g -Wall $*.cpp -o $*.out

# Change these
cxxtestpath = ../../../cxxtest/
testcode    = test_vec.h
test_file	= vector.h
test_files	= dates.cpp Date.cpp WesternDate.cpp Gregorian.cpp Julian.cpp kattistime.cpp

test.out:
	echo '\t Generates test.out ...'
	g++ -g -Wall -o test.out dates.cpp Date.cpp WesternDate.cpp Gregorian.cpp Julian.cpp kattistime.cpp
clean:
	rm -f *.o *.out testcode.cpp

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out
