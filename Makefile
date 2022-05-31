CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: assembler rom

assembler: src/assembler.c
	$(CC) $(CFLAGS) -o assembler src/assembler.c

rom: src/rom.c
	$(CC) $(CFLAGS) -o rom src/rom.c

clean:
	rm assembler
	rm rom
	rm rom.dump
