#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t ret = fork();

	if(ret > 0)
	{

	}

	if(ret == 0)
	{
		//父进程终止后，子进程还活着，变成孤儿进程
		while(1);
	}

	return 0;
}
