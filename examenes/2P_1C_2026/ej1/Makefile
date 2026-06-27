CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := ej1.o ej1_test.o


ej1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej1

ej1.o: ej1.h ej1.c
	$(CC) $(CFLAGS) -c ej1.c

ej1_test.o: ej1.h ej1_test.c
	$(CC) $(CFLAGS) -c ej1_test.c

clean:
	rm *.o
