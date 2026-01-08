#include "csapp.h"

void initjobs()
{
}

void addjob(int pid)
{
}

void deletejob(int pid)
{
}

/* $begin procmask1 */
/* WARNING: This code is buggy! */
void handler(int sig)
{
    int olderrno = errno;
    sigset_t mask_all, prev_all;
    pid_t pid;

    Sigfillset(&mask_all);
    /**
     * 当父进程在 handler 里调用 waitpid(-1, NULL, 0) 时：

它并不是让子进程自己动，而是父进程通过这个系统调用向内核申请：“请把那个已经死掉（僵尸状态）的孩子的信息给我，并把它彻底从系统进程表中抹去。”

内核收到申请，把子进程残留的信息清理干净。

所以： 并不是“自己回收自己”，而是父亲在处理孩子的后事。
     */
    while ((pid = waitpid(-1, NULL, 0)) > 0)
    { /* Reap a zombie child */
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        deletejob(pid); /* Delete the child from the job list */
        Sigprocmask(SIG_SETMASK, &prev_all, NULL);
    }
    if (errno != ECHILD)
        Sio_error("waitpid error");
    errno = olderrno;
}
/**
 * 你可以把这个过程想象成：

1.子进程（临死前）： “爸，我不行了！”（触发 SIGCHLD 信号给内核）。

2.内核： 把孩子停尸，然后拍了拍父亲（父进程）的肩膀。

3.父进程（暂停工作）： 跑进 handler 房间，打了个电话给内核说 waitpid（我要收尸）。

4.内核： 把尸体搬走，销户。

5.父进程： 走出 handler 房间，继续干活。
 */
int main(int argc, char **argv)
{
    int pid;
    sigset_t mask_all, prev_all;
//Sigfillset(&mask_all); // 把 mask_all 填满，包含 SIGCHLD, SIGINT, SIGALRM 等所有信号
//参数 set：指向一个 sigset_t 类型变量的指针。执行后，该变量内部的所有位（bits）都会被置为 1，代表选中了所有信号。
//它通常被用来做一个“全封锁”的准备工作，即告诉内核：“除非我允许，否则我不希望被任何信号干扰。”
    Sigfillset(&mask_all);
    /**
     * 触发 handler 的动作确实是由子进程的“死亡”引起的，但执行者是父进程。

子进程运行结束，内核将其标记为 僵尸状态。

内核发现这个子进程有父亲，于是产生一个 SIGCHLD 信号 发送给父进程。

父进程正在运行（比如在 while(1) 循环里），收到信号后，父进程的执行流被切断，强行跳去执行 handler 函数。

关键点： 此时执行 handler 函数代码的是父进程的 CPU 核心，使用的是父进程的栈空间。
     */
    Signal(SIGCHLD, handler);
    initjobs(); /* Initialize the job list */

    while (1)
    {
        if ((pid = Fork()) == 0)
        { /* Child process */
            /*
            printf("开始替换...\n");
execve("/bin/date", argv, NULL);

// 只要 execve 成功，下面这行代码永远不会执行！
// 因为当前进程的代码段已经变成 /bin/date 的代码了。
printf("我还能回来吗？\n");
*/
            Execve("/bin/date", argv, NULL);
        }
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all); /* Parent process */
        addjob(pid);                                  /* Add the child to the job list */
        Sigprocmask(SIG_SETMASK, &prev_all, NULL);
    }
    exit(0);
}
/* $end procmask1 */
