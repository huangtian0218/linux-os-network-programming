#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
#if 0
	//dup2函数用于复制文件描述符，并且可以自己指定新的文件描述符
	//如果指定的新文件描述符之前已经被使用了，那么会先关闭再使用
	int new_fd = dup2(1, 4);
	printf("new_fd = %d\n", new_fd);

	char* buf = "hello123\n";
	int ret = write(new_fd, buf, strlen(buf));
#endif

	int fd = open("./tmp.txt", O_RDWR | O_CREAT | O_TRUNC);

	dup2(fd, 1);

	printf("[%s]%s(%d)\n", __FILE__, __FUNCTION__, __LINE__);

	return 0;
}
