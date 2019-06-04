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

	write(fd, (void *)"hello", 3);

	//第二个参数表示偏移量，正数向后偏移，负数向前
	//SEEK_SET: 文件起始位置
	//SEEK_CUR: 文件当前位置
	//SEEK_END: 文件末尾位置
	//返回当前读写位置相对于文件开始位置的偏移量，失败返回-1
	lseek(fd, 0, SEEK_SET);

	char buf[30] = {0};
	read(fd, buf, 30);
	printf("%s\n", buf);

	close(fd);

	return 0;
}
