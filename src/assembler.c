#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	FILE* input;
	
	if (argc <= 1) {
		fprintf(stderr, "no arg supp\n");
		exit(EXIT_FAILURE);
	}
	input = fopen(argv[1], "r");
	if (input == NULL) {
		fprintf(stderr, "error opening %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return 0;
}
