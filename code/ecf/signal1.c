#include "csapp.h"
/* $begin signal1 */
/* WARNING: This code is buggy! */

void handler1(int sig)
{
    int olderrno = errno;

    pid_t pid;
    if ((pid = waitpid(-1, NULL, 0)) < 0)
        sio_error("waitpid error");
    char str[20]; // 确保缓冲区足够大

    // 将 num 格式化为字符串存入 str
    snprintf(str, sizeof(str), "%d",pid); 
    Sio_puts(str);
    Sio_puts("  Handler reaped child\n");//reap 回收
    Sleep(1);
    errno = olderrno;
}

int main()
{
    int i, n;
    char buf[MAXBUF];

    if (signal(SIGCHLD, handler1) == SIG_ERR)
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

    //STDIN_FILENO
    //标准输入的文件描述符（值为 0）
    //等同于 stdin的底层描述符
    /* Parent waits for terminal input and then processes it */
    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
        unix_error("read");

    printf("Parent processing input\n");
    while (1)
    {
        sleep(1);
        printf("循环\n");
    }
    exit(0);
}
/* $end signal1 */
