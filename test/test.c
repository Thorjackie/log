#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
        const char* cmd0 = "mov r0, 4";
        const char* cmd1 = "add r0, r1";
        const char* cmd2 = "ldr r0, [sp 4]";

	char *token, *str0, *str1, *str2;

	str0 = strdup(cmd0);
	str1 = strdup(cmd1);
	str2 = strdup(cmd2);

	while ((token = strsep(&str0, ", []"))) {
		printf("(%s) ", token);
	}
	printf("\n");
	while ((token = strsep(&str1, ", []"))) {
		printf("(%s) ", token);
	}
	printf("\n");
	while ((token = strsep(&str2, ", []"))) {
		printf("(%s) ", token);
	}
	printf("\n");

	free(str0);
	free(str1);
	free(str2);
        return 0;
}

