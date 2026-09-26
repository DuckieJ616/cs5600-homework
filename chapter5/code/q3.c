#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        perror("fork");
        exit(1);
    } else if (rc == 0) {
        // Child
        close(pipefd[0]);

        printf("hello\n");
        fflush(stdout);

        write(pipefd[1], "x", 1);
        close(pipefd[1]);
    } else {
        // Parent
        char buffer;

        close(pipefd[1]);

        read(pipefd[0], &buffer, 1);

        printf("goodbye\n");
        close(pipefd[0]);
    }

    return 0;
}
