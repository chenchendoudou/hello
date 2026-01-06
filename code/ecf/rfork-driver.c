#include <stdio.h>
#include <stdlib.h>
#define ITERS 10

int main()
{
	//pid_t pid;
	int i;
	int status;
	for (i = 0; i < ITERS; i++)
	{
		printf("Test %d\n", i);
		fflush(stdout);

		/* Child */
		if (Fork() == 0)
		{
			printf("C%d\n", i);
			fflush(stdout);
			exit(0);
		}

		/* Parent */
		else
		{
			printf("P%d\n", i);
			fflush(stdout);
		}
		fflush(stdout);
		//到达取消点： 当目标线程运行到一个属于“取消点”的函数（如 wait、read、sleep）时，它会检查那个标记。
		//优雅自杀： 如果标记存在，线程会执行清理函数（Cleanup Handlers），然后才正式退出。
		wait(&status);
		//sleep(1);
		fflush(stdout);
	}

	printf("\n");
	fflush(stdout);
	exit(0);
}
