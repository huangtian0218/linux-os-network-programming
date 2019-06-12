#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	pid_t ret = 0;

	ret = fork();
	if(ret > 0)
	{
		int status = 0;
		//等待子进程终止，父进程会进入休眠态
		wait(&status);
		printf("status = %d\n", status);
		if(WIFEXITED(status))
		{
			printf("exited: %d\n", WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status))
		{
			printf("Be killed: %d\n", WTERMSIG(status));
		}
	}

	if(ret == 0)
	{
		extern char **environ;
		//将新程序代码加载到子进程的内存空间，替换掉原来与父进程相同的代码和数据，让子进程运行全新的程序
		execve("./new", argv, environ);
	} 

	return 0;
}
