#include "csapp.h"

int main() 
{
    int i;
    char buf[128];

    for (i = 1; i < 31; i++) {
	sprintf(buf, "%2d", i);
    //它的名字是 "print signal" 的缩写。简单来说，它的作用是将信号编号“翻译”成人类能看懂的文字描述，并输出到标准错误流（stderr）
	psignal(i, buf);
    }
    return 0;
}
