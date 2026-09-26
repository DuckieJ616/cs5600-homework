#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sched.h>

#define NUM_ROUND_TRIPS 100000

void pin_to_cpu0(void) {
    cpu_set_t set;

    CPU_ZERO(&set);
    CPU_SET(0, &set);

    if (sched_setaffinity(0, sizeof(set), &set) == -1) {
        perror("sched_setaffinity");
        exit(1);
    }
}

int main(void) {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        perror("fork");
        exit(1);
    }

    if (rc == 0) {
        // Child process
        pin_to_cpu0();

        close(pipe1[1]);
        close(pipe2[0]);

        char c;

        for (int i = 0; i < NUM_ROUND_TRIPS; i++) {
            read(pipe1[0], &c, 1);
            write(pipe2[1], &c, 1);
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }

    // Parent process
    pin_to_cpu0();

    close(pipe1[0]);
    close(pipe2[1]);

    char c = 'x';
    struct timeval start, end;

    gettimeofday(&start, NULL);

    for (int i = 0; i < NUM_ROUND_TRIPS; i++) {
        write(pipe1[1], &c, 1);
        read(pipe2[0], &c, 1);
    }

    gettimeofday(&end, NULL);

    wait(NULL);

    double elapsed =
        (end.tv_sec - start.tv_sec) * 1000000.0 +
        (end.tv_usec - start.tv_usec);

    printf("Number of round trips: %d\n", NUM_ROUND_TRIPS);
    printf("Total time: %.2f microseconds\n", elapsed);
    printf("Average context switch cost: %.4f microseconds\n",
           elapsed / (NUM_ROUND_TRIPS * 2.0));

    close(pipe1[1]);
    close(pipe2[0]);

    return 0;
}
