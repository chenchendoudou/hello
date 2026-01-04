#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // 子进程逻辑
        printf(" [子进程] 正在运行 (PID: %d)...\n", getpid());
        sleep(3); // 模拟耗时任务
        printf(" [子进程] 任务完成，准备退出。\n");
        exit(88); // 退出码设为 88
    } 
    else {
        // 父进程逻辑
        int status;
        pid_t ret;

        printf(" [父进程] 开始等待子进程，采用非阻塞模式...\n");

        while (1) {
            // WNOHANG 保证了如果没有子进程结束，waitpid 会立即返回 0
            ret = waitpid(pid, &status, WNOHANG);

            if (ret == 0) {
                printf(" [父进程] 子进程还在跑，我先做点别的活...\n");
                sleep(1);
            } 
            else if (ret == pid) {
                if (WIFEXITED(status)) {
                    printf(" [父进程] 检测到子进程退出，退出码: %d\n", WEXITSTATUS(status));
                }
                break; // 子进程处理完了，跳出循环
            } 
            else {
                perror("waitpid error");
                break;
            }
        }
    }
    return 0;
}