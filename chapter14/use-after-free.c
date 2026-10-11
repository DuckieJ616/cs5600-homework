#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *data = malloc(100 * sizeof(int));
    if (data == NULL) return 1;

    data[0] = 100;
    free(data);

    printf("%d\n", data[0]);
    return 0;
}
