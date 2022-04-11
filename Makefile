CC=gcc
CFLAGS=-Wall -Werror

assembler: assembler.c
	$(CC) $(CFLAGS) -o assembler assembler.c
