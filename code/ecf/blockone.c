#include "csapp.h"

int main(int argc, char **argv)
{
/* $begin blockone */
    sigset_t mask, prev_mask;
int condition = 0;
    Sigemptyset(&mask);
    Sigaddset(&mask, SIGINT); 

    /* Block SIGINT and save previous blocked set */
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask);  
    
    /* ...code region that will not be interrupted by SIGINT */
    while (condition++ < 5)
    {
        sleep(1);
        printf("condition = %d\n", condition);
        /* code */
    }
    

    /* Restore previous blocked set, unblocking SIGINT */
    Sigprocmask(SIG_SETMASK, &prev_mask, NULL); 
    sleep(5);//这里能够被ctrl+c终端,如果在blocked区域按下ctrl+c，一旦退出马上就会中断
/* $end blockone */
    exit(0);
}
