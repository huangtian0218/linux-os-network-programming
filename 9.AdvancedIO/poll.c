#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	int ret = -1;
	int mousefd = -1;
	char buf[1024] = {0};
	int coor = 0;
	struct pollfd fds[2];

	//读鼠标
	mousefd = open("/dev/input/mouse0", O_RDONLY);
	if(mousefd == -1)
	{
		printf("%s[%d] %s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	fds[0].fd = 0;
	fds[0].events = POLLIN;

	fds[1].fd = mousefd;
	fds[1].events = POLLIN;

	while(1)
	{
label:	ret = poll(fds, 2, 3000);
		if(ret == -1)
		{
			if(errno == EINTR)
				goto label;
			else
				printf("%s[%d] %s\n", __FUNCTION__, __LINE__, strerror(errno));
		}

		if(ret > 0)
		{
			if(fds[0].events == fds[0].revents)
			{
				ret = read(fds[0].fd, buf, sizeof(buf));
				if(ret > 0)
				{
					printf("keyboard = %s", buf);
				}
			}

			if(fds[1].events == fds[1].revents)
			{
				ret = read(fds[1].fd, &coor, sizeof(coor));
				if(ret > 0)
				{
					printf("mouse = %d", coor);
				}
			}
		}

		if(ret == 0)
		{
			printf("poll time out!\n");
		}
	}

	return 0;
}

