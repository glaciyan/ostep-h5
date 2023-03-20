#define _POSIX_C_SOURCE 1
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child here
        close(STDOUT_FILENO);
        printf("hello? can you hear me?\n");
    }
    else
    {
        // parent
        intmax_t rc_wait = wait(NULL);
        printf("goodbye rc_wait:%jd\n", rc_wait);
    }
}