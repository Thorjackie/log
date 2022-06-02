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

int* parser(char* line, int lineno) {
	int* output = calloc(1, sizeof(int));
	char* token;

	if (!output) {
		fprintf(stderr, "memory allocation error on line %d\n", lineno);
		return NULL;
	}
	while ( (token = strsep(&line, ", []\n")) ) {
		if (strlen(token)) {
			printf("(%s)", token);
		}
	}
	printf("\n");

	free(output);
	return NULL;
}	

int main(int argc, char** argv) {
	// MUST read line by line
	FILE* input;
	char* line = 0;
	int lineno = 0;
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
	    lineno++;
            if (line[0] != '\n') {
                parser(line, lineno);
            }
    }

	free(line);
	return 0;
}
