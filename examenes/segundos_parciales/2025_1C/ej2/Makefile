CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := busADT.o test.o


ej2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej2

test.o: busADT.h test.c
	$(CC) $(CFLAGS) -c test.c

busADT.o: busADT.h busADT.c
	$(CC) $(CFLAGS) -c busADT.c

clean:
	rm *.o
