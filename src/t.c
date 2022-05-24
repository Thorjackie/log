#include <stdio.h>
int main() {

        struct data {
                int arr[10];
                int len;
        };
        
        struct data x = {
                {1, 2, 3, 4},
                sizeof x.arr
        };

        printf("%d\n", x.len);

        return 0;
}
