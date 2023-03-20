#define _POSIX_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int x = 100;
    printf("i am (pid:%jd) x:%d\n", (intmax_t) getpid(), x);
    intmax_t rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        x = 200;
        printf("hello i am child process (pid:%jd) x:%d\n", (intmax_t) getpid(), x);
    }
    else
    {
        x = 150;
        printf("i am the parent of %jd (pid:%jd) x:%d\n", rc, (intmax_t) getpid(), x);
    }

    return 0;
}
