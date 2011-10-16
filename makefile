%.out:	%.cpp
	g++ -m32 -g -Wall $*.cpp -o $*.out

# Change these
cxxtestpath = ../../../cxxtest/
testcode    = test_vec.h
test_file	= vector.h

testcode.cpp: $(testcode)
	$(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

test.out: testcode.cpp
	g++ -o test.out -I $(cxxtestpath) testcode.cpp $(test_file)

clean:
	rm -f *.o *.out testcode.cpp

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out
