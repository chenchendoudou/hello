/* $begin forkprob7 */
#include "csapp.h"
//父进程和子进程虽然看起来都在使用名为 counter 的变量，
//但它们实际上是在各自独立的内存空间中操作自己的那份拷贝。
int counter = 1;

int main()
{
    if (fork() == 0)
    {
        counter--;
        exit(0);
    }
    else
    {
        Wait(NULL);
        printf("counter = %d\n", ++counter);
    }
    exit(0);
}
/* $end forkprob7 */
