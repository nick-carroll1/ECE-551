CC = g++
CXXFLAGS = -std=c++98 -Wall -Werror -pedantic

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

TARGET = circles

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) $(TARGET)

.PHONY: clean
