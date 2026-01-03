#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

pid_t Fork(void)
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        unix_error("Fork error");
    }

    return pid;
}