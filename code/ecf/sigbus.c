#include "csapp.h"

#define START 5
#define END   1<<30
#define INCR  128

char *strsignal(int sig);

long i;

void handler(int sig) {
    printf("%ld\n", i);
    if (sig == SIGBUS) {
	printf("caught %s\n", strsignal(sig));
	exit(0);
    }
    return;
}
/*
1. 核心原因：信号返回后的“原地复活”在 Linux 信号处理机制中，当程序执行一条导致 SIGSEGV（段错误） 的指令（即 x = *(int *)i;）时：
CPU 抛出异常：执行到地址 5 时，发现是非法内存访问。
内核介入：暂停进程，跳去执行你的 handler。
Handler 执行：打印出 5。
返回指令（关键点）：当 handler 执行完毕返回时，默认行为是回到刚才那条出错的指令重新执行。
于是死循环发生了：
返回后，CPU 再次尝试执行 x = *(int *)i;（此时 i 依然是 5）。
再次出错 - 再次进 handler - 再次打印 5 - 再次返回原地。
3. 为什么循环里的 i += INCR 没有执行？因为程序根本没有机会运行到那一步。
在 C 语言的 for 循环中，i += INCR 是在循环体（大括号内的内容）全部成功执行完之后才执行的。
由于你的代码在第一行 x = *(int *)i; 就被内核强行掐断并跳走了，变量 i 的值永远停留在 5，无法自增。
*/
int main() {
    volatile long x;

        Signal(SIGSEGV, handler);
        Signal(SIGBUS, handler);

    for (i = START; i < END; i += INCR) {
        sleep(1);
	x = *(int *)i;
	*(int *)i = x;
		printf("x=%ld\n", x);
    }
    exit(0);
}
