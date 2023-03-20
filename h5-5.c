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
        intmax_t rc_wait = wait(NULL);
        printf("child rc_wait:%jd (pid:%jd)\n", rc_wait, (intmax_t) getpid());
    }
    else
    {
        intmax_t rc_wait = wait(NULL);
        printf("parent rc_wait:%jd (pid:%jd)\n", rc_wait, (intmax_t) getpid());
    }

    return 0;
}
