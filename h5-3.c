#define _POSIX_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
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
        printf("hello\n");
    }
    else
    {
        waitpid(rc, NULL, 0);
        printf("goodbye\n");
    }

    return 0;
}
