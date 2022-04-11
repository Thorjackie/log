#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	FILE* fptr = NULL;
	char* cmd = NULL;
	size_t len = 0;

	if (argc != 2) {
		fprintf(stderr,  "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ((fptr = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "File not found: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&cmd, &len, fptr) != -1) {
		printf("%s", cmd);
	}


	fclose(fptr);
	return 0;
}
