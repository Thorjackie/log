#define _GNU_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
	unsigned int inst: 1;
	unsigned int fop: 1;
	unsigned int lop: 1;
} match;

struct mapping {
	int value;
	char* name;
};

struct mapping Cmds[] = {
	{0x00, "nop"},
	{0x10, "data"},
	{0x20, "load"},
	{0x30, "stor"},
	{0x40, "add"},
	{0x50, "shl"},
	{0x60, "shr"}
};

struct mapping Regs[] = {
	{0x00, "r0"},
	{0x01, "r1"},
	{0x02, "r3"},
	{0x03, "r4"}
};

int mapsize = sizeof(Cmds) / sizeof(struct mapping);

void parseData(char* cmd, int cmd_line) {

	char* inst = NULL;
	char* fop = NULL;
	char* lop = NULL;
	int bytearr[2] = {0};
	int 
	inst = strsep(&cmd, " "); // instruction
	fop = strsep(&cmd, " "); // first operand
	lop = strsep(&cmd, " "); // last operand

	printf("[%s][%s][%s]\n", inst, fop, lop);

	for (int i = 0; i < mapsize; i++) {
		if(!strcmp(inst, Cmds[i].name)) {
			bytearr[0] += Cmds[i].value;
			printf("MATCH: %s\n", Cmds[i].name);
			//match = 1;
		}
		if(i < sizeof(Regs) / sizeof(struct mapping)) {
			if(!strcmp(fop, Regs[i].name)) {
				bytearr[0] += Regs[i].value;
				printf("MATCH: %s\n", Regs[i].name);
			}
			if(!strcmp(lop, Regs[i].name)) {
				bytearr[0] += (Regs[i].value << 2);
				printf("MATCH: %s\n", Regs[i].name);
			}
		}
	}

	//if (match == 0) {
	//	fprintf(stderr, "Error invalid instruction %s on line %d.\n", inst, cmd_line);
	//	exit(EXIT_FAILURE);
	//}

	printf("EOL\n");
}

int main(int argc, char** argv) {

	FILE* fptr = NULL;
	char* cmd = NULL;
	size_t len = 0;
	int line = 0;
	//int* bytes = NULL;

	if (argc != 2) {
		fprintf(stderr,  "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ((fptr = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "File not found: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&cmd, &len, fptr) != -1) {
		line++;
		cmd[strcspn(cmd, "\n")] = 0;
		parseData(cmd, line);
	}


	free(cmd);
	fclose(fptr);
	return 0;
}
