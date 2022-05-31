#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct INST {
	char* name;
	int value;
} INST;

struct bitfield {
	uint8_t inst:1;
	uint8_t op0:1;
	uint8_t op1:1;
};

INST map[] = {
	{"r0", 0x00},
	{"r1", 0x01},
	{"r2", 0x02},
	{"r3", 0x03},
	{"r4", 0x04},
	{"r5", 0x05},
	{"r6", 0x06},
	{"r7", 0x07},
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
int mapsize = sizeof(map) / sizeof(map[0]);

void lexer(char* line, int lineno) {

	int i;
	int output[3] = {0};
	struct bitfield flags = {0};

        char* inst = strtok(line, " ");
        char* op0 = strtok(NULL, ",");
        char* op1 = strtok(NULL, "\n");

	while (op1[0] == ' ') {
		op1++;
	}

	for (i = 0; i < mapsize; i++) {
		if (strcmp(inst, map[i].name) == 0) {
			output[0] += map[i].value;
			flags.inst = 1;
		}
		if (strcmp(op0, map[i].name) == 0) {
			output[1] += map[i].value;
			flags.op0 = 1;
		}
		if (strcmp(op1, map[i].name) == 0) {
			output[1] += (map[i].value << 3);
			flags.op1 = 1;
		}
	}

	if (flags.inst != 1) {
		fprintf(stderr, "line %d: invalid instruction '%s'\n", lineno, inst);
	}
	if (flags.op0 != 1) {
		fprintf(stderr, "line %d: invalid operand '%s'\n", lineno, op0);
	}
	if (flags.op1 != 1) {
		int cnst = atoi(op1);
		if (cnst) {
			output[2] += cnst;
		} else if (op1[0] == '[' && op1[strlen(op1) - 1] == ']') {
			cnst = atoi(strrchr(op1, ' '));
			output[2] += cnst;
		} else {
			fprintf(stderr, "line %d: invalid whatever '%s'\n", lineno, op1);
		}
	}
        printf("%d: %s|%s|%s -> ", lineno, inst, op0, op1);
	printf("[%d][%d][%d]\n", output[0], output[1], output[2]);
	return output;
}

int main(int argc, char** argv) {
	// MUST read line by line
	FILE* input;
	char* line = 0;
	int lineno = 0;
	size_t size = 0;
	int output[3];
	
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
	    lineno++;
            if (line[0] != '\n') {
                lexer(line, lineno);
            }
    }

	free(line);
	return 0;
}
