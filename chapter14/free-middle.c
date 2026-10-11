#include <stdlib.h>

int main(void) {
    int *data = malloc(100 * sizeof(int));
    if (data == NULL) {
        return 1;
    }

    free(data + 10);
    free(data);

    return 0;
}
