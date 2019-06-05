#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	//umask返回旧的文件权限掩码
	mode_t ret = 0;
	ret = umask(0);
	printf("old_mask = %d\n", ret);

	int fd = open("./tmp.txt", O_RDWR | O_CREAT, 0777);

	close(fd);

	return 0;
}
