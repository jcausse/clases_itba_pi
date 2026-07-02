CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := ej2.o ej2_test.o


ej2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej2

ej2.o: ej2.h ej2.c
	$(CC) $(CFLAGS) -c ej2.c

ej2_test.o: ej2.h ej2_test.c
	$(CC) $(CFLAGS) -c ej2_test.c

clean:
	rm *.o
