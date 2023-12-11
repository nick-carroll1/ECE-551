CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3

test: test-bsearch.o search.o
	g++ -o test $(CCFLAGS) test-bsearch.o search.o

test-bsearch.o: test-bsearch.cpp test-bsearch.hpp function.h
	g++ $(CCFLAGS) -c test-bsearch.cpp

search.o: search.cpp function.h
	g++ $(CCFLAGS) -c search.cpp
