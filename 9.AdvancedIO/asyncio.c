#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

static int mousefd;

void signal_fun(int signo)
{
	int coor = 0;
	int ret = -1;

	if(signo == SIGIO)
	{
		ret = read(mousefd, &coor, sizeof(coor));	
		if(ret > 0)
		{
			printf("mouse = %d", coor);
		}
	}
}

int main()
{
	int ret = -1;
	char buf[1024] = {0};
	int coor = 0;
	int flag = -1;

	//读鼠标
	mousefd = open("/dev/input/mouse0", O_RDONLY);
	if(mousefd == -1)
	{
		printf("%s[%d] %s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	//捕获IO信号
	signal(SIGIO, signal_fun);

	//设置当前进程接收SIGIO信号
	fcntl(mousefd, F_SETOWN, getpid());

	//增设异步
	flag = fcntl(mousefd, F_GETFL);
	flag |= O_ASYNC;
	fcntl(mousefd, F_SETFL, flag);

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(0, buf, sizeof(buf));
		if(ret > 0)
		{
			printf("keyboard = %s", buf);
		}
	}

	return 0;
}

