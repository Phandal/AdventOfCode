CC = cc
CFLAGS = -Wall -Wextra
DEBUG = -g

all: clean part1 part2

part1: clean part1.c util.c
	$(CC) $(CFLAGS) $(DEBUG) part1.c util.c -o $@

part2: clean part2.c util.c
	$(CC) $(CFLAGS) $(DEBUG) part2.c util.c -o $@

.PHONY: clean
clean:
	@-rm part1 part2
