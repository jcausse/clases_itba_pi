CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := piersADT.o test.o


ej2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej2

test.o: piersADT.h test.c
	$(CC) $(CFLAGS) -c test.c

piersADT.o: piersADT.h piersADT.c
	$(CC) $(CFLAGS) -c piersADT.c

clean:
	rm *.o
