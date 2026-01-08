#include "csapp.h"

pid_t getpgid(pid_t pid);

void handler(int sig)
{
    if (sig == SIGINT)
        printf("pg     : pid[%5d] pgid[%5d]: received SIGINT\n",
               getpid(), getpgrp());
    else if (sig == SIGTSTP)
        printf("pg     : pid[%5d] pgid[%5d]: received SIGTSTP\n",
               getpid(), getpgrp());
    else
        printf("pg     : unknown signal: %d\n", sig);
}
//这是因为 Ctrl+C 发送信号的对象不是“某个进程”，而是“整个前台进程组（Foreground Process Group）”。
int main()
{
    Signal(SIGINT, handler);
        Signal(SIGTSTP, handler);
    //Fork(): 创建了一个子进程。此时子进程是父进程的副本，PID 不同，但 PGID（进程组 ID）相同
    if (Fork() == 0)
    {
        //execve 会覆盖进程的代码和数据，但它会保留原有的 PID 和 PGID。这意味着 pg 和 pgchild 此时处于同一个进程组中。
        Execve("pgchild", NULL, NULL);
    }

    //getpid() — 获取当前进程 ID
    //getppid() — 获取父进程 ID
    //getpgrp() — 获取进程组 ID
    //getpgid(pid) 函数返回指定 PID 进程所属的组 ID
    //getpgid(getppid()) — 获取父进程的进程组 ID
    printf("pg     : pid[%5d] ppid[%5d] pgid[%5d] ppgid[%5d]: hello\n",
           getpid(), getppid(), getpgrp(), getpgid(getppid()));
    pause();
    exit(0);
}
