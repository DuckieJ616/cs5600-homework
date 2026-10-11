#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *data = malloc(sizeof(int) * 100);

    if (data == NULL) {
        return 1;
    }

    data[0] = 10;
    printf("First element: %d\n", data[0]);

    return 0;
}
