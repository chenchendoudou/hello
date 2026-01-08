/* $begin restart */
#include "csapp.h"

sigjmp_buf buf;

void handler(int sig)
{
    /**
     * #include <setjmp.h>
void siglongjmp(sigjmp_buf env, int val);
env：之前由 sigsetjmp 保存的进程上下文（包含 CPU 寄存器、栈指针以及信号屏蔽字）。
val：跳回目的地后，sigsetjmp 将会返回的值。
     */
    siglongjmp(buf, 1);
}

int main()
{
    /*
    env：用来存储位置信息和进程状态的缓冲区。

savemask：这是它与普通 setjmp 的核心区别。

如果为 非 0：sigsetjmp 会把当前的信号屏蔽字（哪些信号被阻塞了）也存进 env。

如果为 0：则不保存信号屏蔽字。

返回值：

直接调用时：返回 0。

从 siglongjmp 跳回来时：返回非 0 值（由 siglongjmp 的第二个参数决定）。
    */
    if (!sigsetjmp(buf, 1))
    {
        // 当信号触发进入 handler 时，内核会自动阻塞当前信号（防止嵌套）。
        // 如果你用 longjmp 直接跳出 handler，内核可能永远不会解除对该信号的阻塞。结果就是：你的程序之后再也收不到该信号了
        Signal(SIGINT, handler);
        Sio_puts("starting\n");
    }
    else
        Sio_puts("restarting\n");

    while (1)
    {
        Sleep(1);
        Sio_puts("processing...\n");
    }
    exit(0); /* Control never reaches here */
}
/* $end restart */
