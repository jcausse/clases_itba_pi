CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c23 -g -fsanitize=address
INCLUDES := -I../../lib
LIBS := ../../lib/utillist.c

ej01: ej01.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) ej01.c -o ej01

ej02: ej02.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) ej02.c -o ej02

ej03: ej03.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) ej03.c -o ej03

ej09: ej09.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) ej09.c -o ej09

clean:
	find . -type f -name "ej*" ! -name "*.c" -delete
