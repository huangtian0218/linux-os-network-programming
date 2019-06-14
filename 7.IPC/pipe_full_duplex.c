#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int ret = 0;
	char buf[1024] = {0};

	//创建两个pipe实现双向通信
	int pipefd1[2] = {0};	//用于存放管道的读写文件描述符
	int pipefd2[2] = {0};	//用于存放管道的读写文件描述符

	ret = pipe(pipefd1);
	if(ret == -1)
	{
		perror("Error");
		return -1;
	}

	ret = pipe(pipefd2);
	if(ret == -1)
	{
		perror("Error");
		return -1;
	}

	ret = fork();
	if(ret > 0)
	{
		//无名管道单向通信关闭没用到的读文件描述符
		close(pipefd1[0]);
		close(pipefd2[1]);
		while(1)
		{
			//父子进程不能同时先读，否则会阻塞
			write(pipefd1[1], "I am father", strlen("I am father"));
			sleep(1);

			memset(buf, 0, sizeof(buf));
			read(pipefd2[0], buf, sizeof(buf));
			printf("father recv: %s\n", buf);
		}
	}
	else if(ret == 0)
	{
		//无名管道单向通信关闭没用到的写文件描述符
		close(pipefd1[1]);
		close(pipefd2[0]);
		while(1)	
		{
			memset(buf, 0, sizeof(buf));
			read(pipefd1[0], buf, sizeof(buf));
			printf("child recv: %s\n", buf);

			write(pipefd2[1], "I am child", strlen("I am child"));
			sleep(1);
		}
	}

	return 0;
}
