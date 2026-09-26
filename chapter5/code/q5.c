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

        int wc = wait(NULL);
        printf("Child: wait() returned %d\n", wc);
    } else {
        int wc = wait(NULL);

        printf("Parent: wait() returned %d\n", wc);
        printf("Parent: child pid was %d\n", rc);
    }

    return 0;
}
