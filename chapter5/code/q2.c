#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void) {
    int fd = open("q2_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        perror("fork");
        exit(1);
    } else if (rc == 0) {
        // Child process
        write(fd, "Child writes to the file.\n", 26);
        close(fd);
    } else {
        // Parent process
        write(fd, "Parent writes to the file.\n", 27);
        wait(NULL);
        close(fd);
    }

    return 0;
}
