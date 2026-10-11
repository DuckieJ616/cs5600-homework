#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <MB>\n", argv[0]);
        return 1;
    }

    long mb = atol(argv[1]);
    if (mb <= 0) {
        fprintf(stderr, "Memory size must be positive\n");
        return 1;
    }

    size_t size = (size_t)mb * 1024 * 1024;
    int *array = malloc(size);

    if (array == NULL) {
        perror("malloc");
        return 1;
    }

    printf("PID: %d\n", getpid());
    printf("Allocated %ld MB\n", mb);
    fflush(stdout);

    size_t count = size / sizeof(int);

    while (1) {
        for (size_t i = 0; i < count; i++) {
            array[i] += 1;
        }
        sleep(1);
    }

    free(array);
    return 0;
}
