#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <mach/mach.h>
#include <mach/thread_policy.h>

static double elapsed_ns(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1e9 +
           (end.tv_nsec - start.tv_nsec);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pages> <iterations>\n", argv[0]);
        return 1;
    }

    // Request thread affinity on macOS.
    thread_affinity_policy_data_t policy = {1};
    kern_return_t kr = thread_policy_set(
        mach_thread_self(),
        THREAD_AFFINITY_POLICY,
        (thread_policy_t)&policy,
        THREAD_AFFINITY_POLICY_COUNT
    );

    if (kr != KERN_SUCCESS) {
        fprintf(stderr, "Warning: affinity policy not applied\n");
    }

    long pages = atol(argv[1]);
    long iterations = atol(argv[2]);
    long page_size = sysconf(_SC_PAGESIZE);

    if (pages <= 0 || iterations <= 0 || page_size <= 0) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    size_t stride = (size_t)page_size / sizeof(int);
    size_t count = (size_t)pages * stride;

    int *array = calloc(count, sizeof(int));
    if (!array) {
        perror("calloc");
        return 1;
    }

    volatile int *data = array;
    volatile uint64_t sum = 0;

    for (long i = 0; i < pages; i++) {
        data[i * stride] = 1;
    }

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long j = 0; j < iterations; j++) {
        for (long i = 0; i < pages; i++) {
            sum += data[i * stride];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double total_accesses = (double)pages * iterations;
    double ns_per_access = elapsed_ns(start, end) / total_accesses;

    printf("%ld,%ld,%.6f\n", pages, iterations, ns_per_access);

    free(array);
    return 0;
}
