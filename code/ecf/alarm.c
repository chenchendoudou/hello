/* $begin alarm */
#include "csapp.h"

void handler(int sig)
{
    static int beeps = 0;
    printf("pid = %d\n", getpid());
    printf("BEEP\n");
    if (++beeps < 5)
        Alarm(1); /* Next SIGALRM will be delivered in 1 second */
    else
    {
        printf("BOOM!\n");
        exit(0);
    }
}

int main()
{
    Signal(SIGALRM, handler); /* Install SIGALRM handler */
    // alarm 函数主要用于设置一个定时器（闹钟）。当设定的时间到了，系统会向当前进程发送一个 SIGALRM 信号
    Alarm(1); /* Next SIGALRM will be delivered in 1s */
              /*
              “闹钟”是排他的： 注释中提到“之前设置的闹钟”，这说明一个进程同一时间只能有一个 alarm。
              如果你先调了 alarm(10)，5 秒后又调了 alarm(2)，那么之前的 10 秒闹钟就被废了，
              函数会返回 5（剩余时间），并开启新的 2 秒倒计时。
              */
    while (1)
    {
        ; /* Signal handler returns control here each time */
    }
    exit(0);
}
/* $end alarm */
