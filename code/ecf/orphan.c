#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    if (!fork())
    {
        printf("hello,nice to meet you!\n");
        while (1)
            ;
    }
    sleep(1);
    exit(0);
}
