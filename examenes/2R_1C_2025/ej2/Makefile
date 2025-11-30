CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := mostPopularADT.o test.o
EXEC := ej2

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

test.o: mostPopularADT.h test.c
	$(CC) $(CFLAGS) -c test.c

mostPopularADT.o: mostPopularADT.h mostPopularADT.c
	$(CC) $(CFLAGS) -c mostPopularADT.c

clean:
	rm *.o

cleanAll:
	rm *.o
	rm $(EXEC)
