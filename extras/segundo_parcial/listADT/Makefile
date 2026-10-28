CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c23 -g -fsanitize=address

listADT: listADT.c listADT.h listADT_test.c
	$(CC) $(CFLAGS) listADT.c listADT_test.c -o listADT
