#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main() {

        int *ptr;
        int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        ptr = &arr;
        ptr += 2;
        printf("%d\n", *ptr);
        return 0;
}
