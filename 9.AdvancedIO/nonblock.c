#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int mousefd = -1;
	char buf[1024] = {0};
	ssize_t ret = 0;
	int coor = -1;
	int flag = -1;

#if 0
	//读鼠标需要sudo ./a.out
	mousefd = open("/dev/input/mouse0", O_RDONLY|O_NONBLOCK);
	if(mousefd == -1)
	{
		perror("open mouse failed!!!");
		return -1;
	}
#endif

	//重新设置fd=0的标志位
	//fcntl(0, F_SETFL, O_RDONLY|O_NONBLOCK);

	//补充设置fd=0的标志位
	flag = fcntl(0, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(0, F_SETFL, flag);

	while(1)
	{
		ret = read(0, buf, sizeof(buf));
		if(ret > 0)
		{
			printf("%s", buf);
		}
#if 0
		ret = read(mousefd, &coor, sizeof(coor));
		if(ret > 0)
		{
			printf("%u\n", coor);
		}
#endif
	}

	return 0;
}
