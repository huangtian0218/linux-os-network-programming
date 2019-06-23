#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main()
{
	int ret = -1;
	int mousefd = -1;
	fd_set readfs;
	char buf[1024] = {0};
	int coor;
	struct timeval timeout;

	//读鼠标
	mousefd = open("/dev/input/mouse0", O_RDONLY);
	if(mousefd == -1)
	{
		printf("%s[%d] %s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	while(1)
	{
		//设置超时时间
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;

		//清空文件描述符集合
		FD_ZERO(&readfs);
		//将0和mousefd加入文件描述符集合
		FD_SET(0, &readfs);
		FD_SET(mousefd, &readfs);

		//监听0~mouse+1个文件描述符的动静
label:	ret = select(mousefd+1, &readfs, NULL, NULL, &timeout);
		if(ret == -1 && errno == EINTR)
		{
			goto label;
		}
		else if(ret == -1)
		{
			printf("%s[%d] %s\n", __FUNCTION__, __LINE__, strerror(errno));
		}
		else if(ret > 0)
		{
			if(FD_ISSET(0, &readfs))
			{
				//读键盘
				memset(buf, 0, sizeof(buf));
				ret = read(0, buf, sizeof(buf));
				if(ret > 0)
				{
					printf("keyboard = %s", buf);
				}
			}

			if(FD_ISSET(mousefd, &readfs))
			{
				//读鼠标
				ret = read(mousefd, &coor, sizeof(coor));
				if(ret > 0)
				{
					printf("mouse = %d", coor);
				}
			}
		}
		else if(ret == 0)
		{
			printf("select time out!!!\n");
		}
	}

	return 0;
}
