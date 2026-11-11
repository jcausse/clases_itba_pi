CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := ej3.o ej3_test.o


ej3: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej3

ej3.o: ej3.h ej3.c
	$(CC) $(CFLAGS) -c ej3.c

ej3_test.o: ej3.h ej3_test.c
	$(CC) $(CFLAGS) -c ej3_test.c

clean:
	rm -f *.o ej3
