CC := gcc
CFLAGS := -Wall -pedantic -std=c23 -g -fsanitize=address
OBJS := landmark.o landmark_test.o


ej2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ej2

landmark_test.o: landmark.h landmark_test.c
	$(CC) $(CFLAGS) -c landmark_test.c

landmark.o: landmark.h landmark.c
	$(CC) $(CFLAGS) -c landmark.c

clean:
	rm *.o
