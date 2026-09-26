#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int x = 100;

    printf("Before fork: x = %d\n", x);

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("Child: x = %d\n", x);
        x = 200;
        printf("Child after changing x: x = %d\n", x);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent: x = %d\n", x);
        x = 300;
        printf("Parent after changing x: x = %d\n", x);
    }

    return 0;
}
