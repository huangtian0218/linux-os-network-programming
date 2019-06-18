#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define FIFONAME1 "./fifo1"
#define FIFONAME2 "./fifo2"

void signal_fun(int signo)
{
	remove("./fifo");
	exit(-1);
}

int call_mkfifo(const char *pathname, mode_t mode)
{
	int ret = -1;
	int fd = -1;

	ret = mkfifo(pathname, 0644);
	if(ret == -1)
	{
		perror("Error");
	}

	fd = open(pathname, mode);
	if(fd == -1)
	{
		perror("Error");
		return -1;
	}

	return fd;
}

int main()
{
	int fd1 = -1;
	int fd2 = -1;
	int ret = -1;
	char buf[1024] = {0};
	
	fd1 = call_mkfifo(FIFONAME1, O_RDONLY);
	fd2 = call_mkfifo(FIFONAME2, O_WRONLY);

	ret = fork();
	if(ret > 0)
	{
		//捕获中断信号
		signal(SIGINT, signal_fun);

		while(1)
		{
			memset(buf, 0, sizeof(buf));
			scanf("%s", buf);
			write(fd2, buf, sizeof(buf));
		}
	}
	else if(ret == 0)
	{
		while(1)
		{
			memset(buf, 0, sizeof(buf));
			read(fd1, buf, sizeof(buf));
			printf("recv: buf = %s\n", buf);
		}
	}

	return 0;
}
