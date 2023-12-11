CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
#cyoa-step1: $(OBJS)
#	g++ -o cyoa-step1 $(CCFLAGS) $(OBJS)

#%.o: %.cpp %.hpp
#	g++ $(CCFLAGS) -c $<


cyoa-step4: cyoa-step4.o story.o textParser.o
	g++ -o cyoa-step4 $(CCFLAGS) cyoa-step4.o story.o textParser.o

cyoa-step4.o: cyoa-step4.cpp textParser.hpp story.hpp story.o
	g++ $(CCFLAGS) -c cyoa-step4.cpp

cyoa-step3: cyoa-step3.o dfs.o story.o textParser.o
	g++ -o cyoa-step3 $(CCFLAGS) cyoa-step3.o dfs.o textParser.o story.o

cyoa-step3.o: cyoa-step3.cpp dfs.hpp textParser.hpp story.hpp
	g++ $(CCFLAGS) -c cyoa-step3.cpp

dfs.o: dfs.hpp story.hpp dfs.cpp
	g++ $(CCFLAGS) -c dfs.cpp

cyoa-step2: cyoa-step2.o textParser.o story.o
	g++ -o cyoa-step2 $(CCFLAGS) cyoa-step2.o textParser.o story.o

cyoa-step2.o: cyoa-step2.cpp story.hpp textParser.hpp
	g++ $(CCFLAGS) -c cyoa-step2.cpp

cyoa-step1: cyoa-step1.o textParser.o story.o
	g++ -o cyoa-step1 $(CCFLAGS) cyoa-step1.o textParser.o story.o

cyoa-step1.o: cyoa-step1.cpp textParser.hpp story.hpp
	g++ $(CCFLAGS) -c cyoa-step1.cpp

textParser.o: textParser.cpp textParser.hpp story.hpp
	g++ $(CCFLAGS) -c textParser.cpp

story.o: story.cpp story.hpp
	g++ $(CCFLAGS) -c story.cpp
