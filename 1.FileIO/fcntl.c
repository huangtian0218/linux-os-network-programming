#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd = 0;
	fd = open("./tmp.txt", O_RDWR | O_CREAT | O_TRUNC);
	if(-1 == fd)
	{
		printf("open failed!\n");
		return -1;
	}

#if 0
	//fcntl模拟dup重定向
	close(1);
	fcntl(fd, F_DUPFD, 0);
	printf("[%s]%s(%d)\n", __FILE__, __FUNCTION__, __LINE__);

	//fcntl模拟dup2重定向，第三个参数是你要复制的文件描述符
	close(1);	
	fcntl(fd, F_DUPFD, 1);
	printf("[%s]%s(%d)\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	//fcntl补设O_APPEND标志位
	//F_SETFL: 设置新的标志位
	//F_GETFL: 获取标志位，第三个参数写0
	//fcntl(fd, F_SETFL, O_RDWR | O_APPEND);
	int flag = fcntl(fd, F_GETFL, 0);
	flag = flag | O_APPEND;
	fcntl(fd, F_SETFL, flag);

	close(fd);

	return 0;
}
