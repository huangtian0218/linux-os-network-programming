#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
#if 0
	//dup函数用于复制文件描述符，返回一个新的文件描述符
	//新文件描述符和旧文件描述符指向同一张文件表，共享文件位移量
	int new_fd = dup(1);
	printf("new_fd = %d\n", new_fd);

	char* buf = "hello123\n";
	int ret = write(new_fd, buf, strlen(buf));
#endif

	//用dup实现重定位
	int fd = open("./tmp.txt", O_RDWR | O_CREAT | O_TRUNC);

	close(1);

	//1被关闭后，会复制到1上，因为dup会找最小没被用的文件描述符
	int fd2 = dup(fd);
	//1被关闭后，printf不会打印到屏幕上，而是重定向到fd所指向的文件
	printf("fd2 = %d\n", fd2);
	printf("[%s]%s(%d)\n", __FILE__, __FUNCTION__, __LINE__);

	return 0;
}
