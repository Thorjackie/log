#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main() {
        uint8_t minuend = 8;
        uint8_t subtrahend = 3;
        bool carry = 0;

        subtrahend = ~subtrahend;
        minuend += subtrahend + ~carry;
        printf("%d\n", minuend);

        return 0;
}
