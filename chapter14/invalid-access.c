#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *data = malloc(sizeof(int) * 100);

    if (data == NULL) {
        return 1;
    }

    data[100] = 42;

    free(data);
    return 0;
}
