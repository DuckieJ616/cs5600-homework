#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <time.h>

int main(void) {
    struct timespec resolution;

    if (clock_getres(CLOCK_MONOTONIC, &resolution) != 0) {
        perror("clock_getres");
        return 1;
    }

    printf("Clock resolution: %ld seconds, %ld nanoseconds\n",
           resolution.tv_sec, resolution.tv_nsec);

    struct timespec start, end;
    long long min_diff = 0;

    for (int i = 0; i < 1000000; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &end);

        long long diff =
            (end.tv_sec - start.tv_sec) * 1000000000LL +
            (end.tv_nsec - start.tv_nsec);

        if (diff > 0 && (min_diff == 0 || diff < min_diff)) {
            min_diff = diff;
        }
    }

    printf("Minimum observed positive interval: %lld ns\n", min_diff);

    return 0;
}
