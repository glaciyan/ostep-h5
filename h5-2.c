#define _POSIX_C_SOURCE 1
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    printf("i am (pid:%jd)\n", (intmax_t) getpid());

    const char *content = "hallo";
    size_t contentSize = (size_t) 5;

    const char *content2 = "guten";
    size_t contentSize2 = (size_t) 5;

    const char *fileName = "h5-2.txt";
    int fd = open(fileName, O_CREAT | O_WRONLY, S_IRWXU);
    if (fd == -1)
    {
        perror(fileName);
        exit(1);
    }

    intmax_t rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        intmax_t written = write(fd, content2, contentSize2);
        close(fd);

        if (written == -1)
        {
            perror(fileName);
            exit(1);
        }
        else if ((uintmax_t) written < contentSize2)
        {
            fprintf(stderr, "volle datei konnte nicht geschrieben werden\n");
            exit(1);
        }

        printf("hello i am child process (pid:%jd)\n", (intmax_t) getpid());
    }
    else
    {
        intmax_t written = write(fd, content, contentSize);
        close(fd);

        if (written == -1)
        {
            perror(fileName);
            exit(1);
        }
        else if ((uintmax_t) written < contentSize)
        {
            fprintf(stderr, "volle datei konnte nicht geschrieben werden\n");
            exit(1);
        }

        printf("i am the parent of %jd (pid:%jd)\n", rc, (intmax_t) getpid());
    }

    return 0;
}
