CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := courseADT.o test.o


ej1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej1

test.o: courseADT.h test.c
	$(CC) $(CFLAGS) -c test.c

courseADT.o: courseADT.h courseADT.c
	$(CC) $(CFLAGS) -c courseADT.c

clean:
	rm *.o
