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
        intmax_t rc_wait = waitpid(-1, NULL, 0);
        printf("child rc_wait:%jd (pid:%jd)\n", rc_wait, (intmax_t) getpid());
    }
    else
    {
        printf("parent is waiting for child:%jd\n", (intmax_t) rc);
        intmax_t rc_wait = waitpid(rc, NULL, 0);
        printf("parent rc_wait:%jd (pid:%jd)\n", rc_wait, (intmax_t) getpid());
    }

    return 0;
}
