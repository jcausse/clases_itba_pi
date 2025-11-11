CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := busDriverADT.o test.o
EXEC := ej1

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

test.o: busDriverADT.h test.c
	$(CC) $(CFLAGS) -c test.c

busDriverADT.o: busDriverADT.h busDriverADT.c
	$(CC) $(CFLAGS) -c busDriverADT.c

clean:
	rm *.o

cleanAll:
	rm *.o
	rm $(EXEC)
