#define _POSIX_C_SOURCE 1
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    // parent and 2 children processes will have a copy of the open fd
    // each of which will have their own handle
    // this is why we have to close all of them in each process

    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid_t rc[2];
    rc[0] = fork();

    if (rc[0] < 0)
    {
        fprintf(stderr, "one fork failed\n");
        exit(1);
    }
    else if (rc[0] == 0)
    {
        // first child

        // every process should close all pipes
        if (close(pipefd[0]) == -1)
        {
            perror("first child read pipe");
            exit(1);
        }

        // set stdout to our pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            perror("first child dup2");
            exit(1);
        }

        printf("hello");
        fflush(stdout);

        sleep(2);

        printf(" ");
        printf("kevin");
        fflush(stdout);
        for (int i = 0; i < 2; i++)
        {
            sleep(1);
            printf("!");
            fflush(stdout);
        }

        if (close(pipefd[1]) == -1)
        {
            perror("first child write pipe");
            exit(1);
        }

        exit(0);
    }
    else
    {
        // in parent
        rc[1] = fork();

        if (rc[1] < 0)
        {
            fprintf(stderr, "second fork failed\n");
            exit(1);
        }
        else if (rc[1] == 0)
        {
            // second child

            // start closing all files
            if (close(pipefd[1]) == -1)
            {
                perror("second child write pipe");
                exit(1);
            }

            char buff[256];
            intmax_t hasRead;
            while ((hasRead = read(pipefd[0], &buff, 256)) > 0)
            {
                intmax_t writeRes = write(STDOUT_FILENO, &buff, hasRead);

                if (writeRes == -1)
                {
                    perror("write to stdout");
                    exit(1);
                }
                else if (writeRes < hasRead)
                {
                    fprintf(stderr, "couldn't write everything to stdout\n");
                    exit(1);
                }
            }
            printf("\n");

            if (close(pipefd[0]) == -1)
            {
                perror("second child read pipe");
                exit(1);
            }
            exit(0);
        }
        else
        {
            // back to parent
            if (close(pipefd[0]) == -1)
            {
                perror("parent read pipe");
                exit(1);
            }

            if (close(pipefd[1]) == -1)
            {
                perror("parent write pipe");
                exit(1);
            }

            intmax_t rc_wait[2];
            rc_wait[0] = waitpid(rc[0], NULL, 0);
            rc_wait[1] = waitpid(rc[1], NULL, 0);

            if ((rc_wait[0] == -1) | (rc_wait[1] == -1))
            {
                perror("parent wait");
                exit(1);
            }

            printf("goodbye from pid:%jd, 1st child pid:%jd, 2nd child pid:%jd\n", (intmax_t) getpid(), rc_wait[0],
                   rc_wait[1]);
        }
    }

    return 0;
}