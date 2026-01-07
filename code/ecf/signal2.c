#include "csapp.h"

/* $begin signal2 */
void handler2(int sig)
{
    int olderrno = errno;
    int static ci = 0;
    printf("第%d次进入handler2\n",++ci);
    sleep(1);
    while (waitpid(-1, NULL, 0) > 0)
    {
        Sio_puts("Handler reaped child\n");
    }
    if (errno != ECHILD)
        Sio_error("waitpid error");
    Sleep(1);
    errno = olderrno;
}
/* $end signal2 */

int main()
{
    int i, n;
    char buf[MAXBUF];

    //一旦内核把进程从正常执行流“劫持”到信号处理函数（Handler）的那一瞬间，该信号的 pending 位就会被清零（重置为 0）。
    if (signal(SIGCHLD, handler2) == SIG_ERR)
        unix_error("signal error");

    /* Parent creates children */
    for (i = 0; i < 3; i++)
    {
        if (Fork() == 0)
        {
            printf("Hello from child %d\n", (int)getpid());
            exit(0);
        }
    }

    /* Parent waits for terminal input and then processes it */
    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
        unix_error("read");

    printf("Parent processing input\n");
    while (1)
        ;

    exit(0);
}
