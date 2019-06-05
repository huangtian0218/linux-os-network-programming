#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd = open("./tmp.txt", O_RDWR | O_CREAT);

	//截断该文件成3个字符
	ftruncate(fd, 3);

	close(fd);

	return 0;
}
