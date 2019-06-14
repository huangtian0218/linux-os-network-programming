#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int ret = 0;
	int pipefd[2] = {0};	//用于存放管道的读写文件描述符

	ret = pipe(pipefd);
	if(ret == -1)
	{
		perror("Error");
		return -1;
	}

	ret = fork();
	if(ret > 0)
	{
		//无名管道单向通信关闭没用到的读文件描述符
		close(pipefd[0]);
		while(1)
		{
			write(pipefd[1], "I am father", strlen("I am father"));
			sleep(1);
		}
	}
	else if(ret == 0)
	{
		//无名管道单向通信关闭没用到的写文件描述符
		close(pipefd[1]);
		//如果父子进程的读文件描述符都被关闭，那么往管道写数据时内核会发送SIGPIPE信号
		//close(pipefd[0]);
		while(1)	
		{
			char buf[1024] = {0};
			read(pipefd[0], buf, sizeof(buf));
			printf("child: buf = %s\n", buf);
		}
	}

	return 0;
}
