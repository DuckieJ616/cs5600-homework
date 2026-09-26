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
        printf("Child: pid = %d\n", getpid());
        sleep(1);
        printf("Child: finished\n");
    } else {
        int status;

        printf("Parent: waiting for child %d\n", rc);

        int wc = waitpid(rc, &status, 0);

        printf("Parent: waitpid() returned %d\n", wc);
    }

    return 0;
}
