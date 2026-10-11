#include <stdlib.h>

int main(void) {
    int *ptr = malloc(sizeof(int));

    if (ptr == NULL) {
        return 1;
    }

    free(ptr);
    free(ptr);

    return 0;
}
