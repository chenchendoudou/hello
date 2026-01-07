#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "csapp.h"

/* $begin signalprob0 */
volatile long counter = 2;

void handler1(int sig) 
{
    sigset_t mask, prev_mask;
    Sigfillset(&mask);
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask);  /* Block sigs */
    Sio_putl(--counter);
    printf("\n");
    Sigprocmask(SIG_SETMASK, &prev_mask, NULL); /* Restore sigs */

printf("进程 %d 收到信号\n", getpid());
    _exit(0);
}

int main() 
{
    pid_t pid;
    sigset_t mask, prev_mask;
printf("进程 %d 收到信号\n", getpid());
    printf("%ld\n", counter);
    fflush(stdout);

    signal(SIGUSR1, handler1);
    if ((pid = Fork()) == 0) {
        while(1) {};
    }
    Kill(pid, SIGUSR1); 
    Waitpid(-1, NULL, 0);

    Sigfillset(&mask);
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask);  /* Block sigs */
    printf("%ld\n", ++counter);
    Sigprocmask(SIG_SETMASK, &prev_mask, NULL); /* Restore sigs */

    exit(0);
}
/* $end signalprob0 */
