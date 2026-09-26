#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    int child1 = fork();

    if (child1 < 0) {
        perror("fork");
        exit(1);
    }

    if (child1 == 0) {
        // First child: write to pipe
        close(pipefd[0]);

        char message[] = "Hello from child 1\n";
        write(pipefd[1], message, sizeof(message) - 1);

        close(pipefd[1]);
        exit(0);
    }

    int child2 = fork();

    if (child2 < 0) {
        perror("fork");
        exit(1);
    }

    if (child2 == 0) {
        // Second child: read from pipe
        close(pipefd[1]);

        char buffer[100];
        int n = read(pipefd[0], buffer, sizeof(buffer) - 1);

        if (n > 0) {
            buffer[n] = '\0';
            printf("Child 2 received: %s", buffer);
        }

        close(pipefd[0]);
        exit(0);
    }

    // Parent does not use the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}
