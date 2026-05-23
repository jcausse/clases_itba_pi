CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c23 -g -fsanitize=address
INCLUDES := -I../../lib
LIBS := ../../lib/utillist.c

ej09: ej09.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) ej09.c -o ej09

clean:
	find . -type f -name "ej*" ! -name "*.c" -delete
