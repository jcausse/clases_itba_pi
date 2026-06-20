CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c23 -g -fsanitize=address

ej13: ej13.c ej13.h ej13_test.c
	$(CC) $(CFLAGS) -o ej13 ej13.c ej13_test.c

clean:
	rm ej13
