CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := coursesADT.o test.o


ej1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej1

test.o: coursesADT.h test.c
	$(CC) $(CFLAGS) -c test.c

coursesADT.o: coursesADT.h coursesADT.c
	$(CC) $(CFLAGS) -c coursesADT.c

clean:
	rm *.o

