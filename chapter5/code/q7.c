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
        close(STDOUT_FILENO);

        printf("Child: can you see this?\n");
        fflush(stdout);
    } else {
        wait(NULL);
        printf("Parent: child finished\n");
    }

    return 0;
}
