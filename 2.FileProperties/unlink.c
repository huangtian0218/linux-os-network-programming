#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
	unlink("./a.out");

	//利用unlink创建临时文件
	int fd = open("./tmp.txt", O_RDWR | O_CREAT, 0664);
	unlink("./tmp.txt");

	write(fd, "test unlink\n", strlen("test unlink\n"));

	lseek(fd, 0, SEEK_SET);

	char buf[30] = {0};
	read(fd, buf, sizeof(buf));
	printf("buf = %s\n", buf);

	return 0;
}
