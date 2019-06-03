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

	//write成功返回写入的字符个数，失败返回-1
	int ret = write(fd, (void *)"hello", 5);
	printf("ret = %ld\n", ret);

	close(fd);

	return 0;
}
