CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := counters.o test.o


ej1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej1

test.o: counters.h test.c
	$(CC) $(CFLAGS) -c test.c

counters.o: counters.h counters.c
	$(CC) $(CFLAGS) -c counters.c

clean:
	rm *.o
