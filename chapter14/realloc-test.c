#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *data = malloc(5 * sizeof(int));

    if (data == NULL) {
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        data[i] = i + 1;
    }

    int *temp = realloc(data, 10 * sizeof(int));

    if (temp == NULL) {
        free(data);
        return 1;
    }

    data = temp;

    for (int i = 5; i < 10; i++) {
        data[i] = i + 1;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", data[i]);
    }

    printf("\n");
    free(data);

    return 0;
}
