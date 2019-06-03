#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd = 0;

	fd = open("./1.txt", O_RDWR);
	if(-1 == fd)
	{
		printf("open failed!\n");
		return -1;
	}

	//read成功返回读取的字符个数，失败返回-1
	char buf[30] = {0};
	int ret = read(fd, buf, 30);
	printf("buf = %s, ret = %d\n", buf, ret);

	close(fd);

	return 0;
}
