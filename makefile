%.out:	%.cpp
	g++ -m32 -g -Wall $*.cpp -o $*.out

# Change these
OBJ_DATE 	= date.cpp westerndate.cpp
OBJ_GJK		= gregorian.cpp julian.cpp kattistime.cpp
OBJ_ALL	 	= cprog09lab22c.cpp date.cpp westerndate.cpp gregorian.cpp julian.cpp kattistime.cpp
OBJ_GREG 	= cprog09lab22b.cpp date.cpp westerndate.cpp gregorian.cpp kattistime.cpp
OBJ_JULI 	= cprog09lab22a.cpp date.cpp westerndate.cpp julian.cpp kattistime.cpp

datetest.out:
	echo Generates datetest.out ...
	g++ -g -Wall -o datetest.out datetest.cpp $(OBJ_DATES) 

dates.out:
	echo Generates dates.out ...
	g++ -g -Wall -o dates.out dates.cpp $(OBJ_DATE) $(OBJ_GJK)

gregorian_tests:
	echo Generating Gregorian tests
	g++ -g -Wall -o gregorian_tests.out $(OBJ_GREG)

julian_tests:
	echo Generating Julian tests
	g++ -g -Wall -o julian_tests.out $(OBJ_JULI)
	cat oldkattis/lab22a.in | ./julian_tests.out > julian_tests.txt

gregorian_and_julian_tests:
	echo Generating Gregorian and Julian tests
	g++ -g -Wall -o gregorian_and_julian_tests.out $(OBJ_ALL)
	cat oldkattis/lab22c.in | ./gregorian_and_julian_tests.out > gregorian_and_julian_tests.txt

clean:
	rm -f *.o *.out testcode.cpp

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out
