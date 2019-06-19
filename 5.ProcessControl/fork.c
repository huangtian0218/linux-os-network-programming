#include <stdio.h>
#include <unistd.h>

int main()
{
	//fork之前的代码子进程只复制，但不会执行，只有父进程会执行
	printf("before fork...\n");

	pid_t ret = fork();
	if(ret > 0)
	{
		printf("parent...\n");
	}

	if(ret == 0)
	{
		printf("child...\n");
	}

	printf("%d: ret = %d\n", getpid(), ret);

	while(1);

	return 0;
}
