#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int rc = fork();

    if (rc < 0) {
        perror("fork");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("Child: before exec\n");
        fflush(stdout);

        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);

        // Only runs if execvp() fails
        perror("execvp");
        exit(1);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent: child finished\n");
    }

    return 0;
}
