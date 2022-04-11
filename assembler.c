#define _GNU_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cmd {
	int value;
	char* name;
};

struct Cmd Cmds[] = {
	{0x00, "nop"},
	{0x10, "data"},
	{0x20, "load"},
	{0x30, "stor"}
};

int CmdLen = sizeof(Cmds) / sizeof(struct Cmd);

void parseData(char* cmd) {

	char* tok = NULL;

	while ((tok = strsep(&cmd, " "))) {
		for ( int i = 0; i < CmdLen; i++) {
			if (tok == Cmds[i].name) {
				printf("oooh found one \n");
			}
		}
	}
}

int main(int argc, char** argv) {

	FILE* fptr = NULL;
	char* cmd = NULL;
	size_t len = 0;
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
		cmd[strcspn(cmd, "\n")] = 0;
		parseData(cmd);
	}


	free(cmd);
	fclose(fptr);
	return 0;
}
