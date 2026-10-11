#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int x = 10;
    int *ptr = &x;

    free(ptr);

    return 0;
}
