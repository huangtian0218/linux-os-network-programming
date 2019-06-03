#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	//程序开始运行时，默认会调用下面这行，返回的文件描述符是0
	//open("/dev/stdin", O_RDONLY);
	
	char buf[30] = {0};
	int ret = read(0, buf, 30);
	printf("buf = %s, ret = %d\n", buf, ret);

	return 0;
}
