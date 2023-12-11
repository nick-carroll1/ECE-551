CFLAGS=-Wall -pedantic -std=gnu99 -Werror -ggdb3

minesweeper: minesweeper.o future.o
	gcc -o minesweeper $^

%.o: %.c
	gcc -c $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f *~ minesweeper.o minesweeper
