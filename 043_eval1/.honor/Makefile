CFLAGS=-std=gnu99 -Werror -Wall -pedantic -ggdb3
all: printSsData printFilteredSsData printLocalMax printSsPeriod
print%: print%.o sunspots.c
	gcc $(CFLAGS) sunspots.c $< -o $@

.PHONY: clean
clean:
	rm -f *~ printSsData printFilteredSsData printLocalMax printSsPeriod
