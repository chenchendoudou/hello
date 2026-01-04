/* $begin forkprob2 */
#include "csapp.h"

void end(void) 
{
    printf("2"); fflush(stdout);
}


int main() 
{
    if (Fork() == 0)
    { 
	atexit(end);//该子进程结束时，调用end函数
    //执行 atexit(end)，注册了退出处理函数。关键点： 此时 P1 及其未来的子进程在退出时都会调用 end。
    }
    if (Fork() == 0) {
	printf("0"); fflush(stdout); 
    }
    else {
        printf("1"); fflush(stdout); 
    }
    exit(0);
}
/* $end forkprob2 */

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cleanup_files() {
    printf("[清理] 正在关闭所有已打开的日志文件...\n");
}

void release_memory() {
    printf("[清理] 正在释放全局内存缓冲池...\n");
}

void goodbye() {
    printf("[清理] 程序结束，再见！\n");
}

int main() {
    // 注册清理函数 atexit用于注册程序正常终止时需要执行的处理函数。它允许开发者在程序结束前执行特定的清理操作。
    atexit(goodbye);       // 第1个注册，最后执行
    atexit(release_memory); // 第2个注册
    atexit(cleanup_files);  // 第3个注册，最先执行

    printf("程序正在运行中...\n");
    sleep(1);

    printf("决定退出程序。\n");
    
    // 无论是执行 exit() 还是 return 0，都会触发 atexit 函数
    exit(0); 
}

程序正在运行中...
决定退出程序。
[清理] 正在关闭所有已打开的日志文件...
[清理] 正在释放全局内存缓冲池...
[清理] 程序结束，再见！

*/