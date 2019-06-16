#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

void signal_fun(int signo)
{
	remove("./fifo");
	exit(-1);
}

int main()
{
	int ret = 0;
	int fd = -1;
	char buf[1024] = {0};
	
	//捕获中断信号
	signal(SIGINT, signal_fun);

	ret = mkfifo("./fifo", 0644);
	if(ret == -1)
	{
		perror("Error");
	}

	fd = open("./fifo", O_WRONLY);
	if(fd == -1)
	{
		perror("Error");
		return -1;
	}

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		scanf("%s", buf);
		write(fd, buf, sizeof(buf));
	}

	return 0;
}
