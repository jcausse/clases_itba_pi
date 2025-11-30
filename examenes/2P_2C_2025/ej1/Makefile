CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := socialADT.o test.o


ej1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej1

test.o: socialADT.h test.c
	$(CC) $(CFLAGS) -c test.c

socialADT.o: socialADT.h socialADT.c
	$(CC) $(CFLAGS) -c socialADT.c

clean:
	rm *.o
