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
        printf("i am child pid:%jd\n", (intmax_t) getpid());

        const char *program = "ls";

        execlp(program, program, "..", (char *) NULL);
        perror(program);
    }
    else
    {
        intmax_t rc_wait = waitpid(rc, NULL, 0);
        printf("goodbye rc_wait:%jd\n", rc_wait);
    }

    return 0;
}
