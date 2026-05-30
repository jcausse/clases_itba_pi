CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c23 -g -fsanitize=address

ej12: ej12.c ej12.h ej12_test.c
	$(CC) $(CFLAGS) -o ej12 ej12.c ej12_test.c

clean:
	rm ej12
