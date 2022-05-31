#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
        char* cmd0 = "mov r0, 4";
        char* cmd1 = "add r0, r1";
        char* cmd2 = "ldr r0, [sp 4]";

        char* data0 = strchr(cmd0, ',');
        char* data1 = strchr(cmd1, ',');
        char* data2 = strchr(cmd2, ',');

        data0 += 2;
        data1 += 2;
        data2 += 2;

        printf("(%s)\n(%s)\n(%s)\n", data0, data1, data2);

        return 0;
}

