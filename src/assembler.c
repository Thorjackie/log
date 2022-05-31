#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct INST {
	char* name;
	int value;
} INST;

INST map[] = {
	{"mov", 0x04},
	{"ldr", 0x08},
	{"str", 0x0c},
	{"add", 0x10},
	{"and", 0x14},
	{"not", 0x18},
	{"cmp", 0x1c},
	{"jmp", 0x20},
	{"jpc", 0x24}
};

INST registers[] = {
	{"r0", 0x00},
	{"r1", 0x01},
	{"r2", 0x02},
	{"r3", 0x03},
	{"r4", 0x04},
	{"r5", 0x05},
	{"r6", 0x06},
	{"r7", 0x07}
};

void lexer(char* line, int width) {
        int output[2] = {0};

        char* first = strtok(line, " ");
        char* sec = strtok(NULL, ",");
        char* thr = strtok(NULL, "\n");

        if (thr[0] == ' ') {
                thr++;
        }

        printf("%d: (%s)(%s)(%s)\n", width, first, sec, thr);
}

int main(int argc, char** argv) {
	// MUST read line by line
	FILE* input;
	char* line = 0;
	size_t size = 0;
	
	if (argc <= 1) {
		fprintf(stderr, "no arg supp\n");
		exit(EXIT_FAILURE);
	}
	input = fopen(argv[1], "r");
	if (input == NULL) {
		fprintf(stderr, "error opening %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
    
    while (getline(&line,  &size, input) != -1) {
            if (line[0] != '\n') {
                lexer(line, size);
            }
    }

	free(line);
	return 0;
}
