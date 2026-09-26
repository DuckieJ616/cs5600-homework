#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_CALLS 1000000

int main(void) {
    struct timeval start, end;

    gettimeofday(&start, NULL);

    for (int i = 0; i < NUM_CALLS; i++) {
        read(STDIN_FILENO, NULL, 0);
    }

    gettimeofday(&end, NULL);

    double elapsed =
        (end.tv_sec - start.tv_sec) * 1000000.0 +
        (end.tv_usec - start.tv_usec);

    printf("Number of system calls: %d\n", NUM_CALLS);
    printf("Total time: %.2f microseconds\n", elapsed);
    printf("Average system call cost: %.4f microseconds\n",
           elapsed / NUM_CALLS);

    return 0;
}
