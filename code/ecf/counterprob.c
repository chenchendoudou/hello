/* $begin counterprob */
#include "csapp.h"

int counter = 0;

void handler(int sig)
{
    counter++;
            printf("handler child pid = %d\n", getpid());
    sleep(1); /* Do some work in the handler */
    return;
}

int main()
{
    int i;

    //信号是发送给特定进程的，谁收到信号，谁就去执行 handler。
    Signal(SIGUSR2, handler);

    if (Fork() == 0)
    { /* Child */
            printf("child pid = %d\n", getpid());
        for (i = 0; i < 5; i++)
        {
            //pid (进程 ID)：指定接收信号的目标。

//sig (信号编号)：指定发送哪种信号（如 SIGKILL、SIGTERM、SIGUSR1 等）
            Kill(getppid(), SIGUSR2);
            printf("sent SIGUSR2 to parent\n");
            //sleep(1);
        }
        exit(0);
    }

    Wait(NULL);
    printf("counter=%d\n", counter);
    exit(0);
}
/* $end counterprob */
