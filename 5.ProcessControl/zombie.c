#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t ret = fork();

	if(ret > 0)
	{
		while(1);
	}

	if(ret == 0)
	{
		//父进程活着，子进程终止后不再运行，但是没有被回收资源，子进程变成僵尸进程
	}

	return 0;
}
