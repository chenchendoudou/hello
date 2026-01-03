#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    printf("current process is %d\n", getpid());
    
    return 0;
}