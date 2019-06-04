#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
	//程序开始运行时，默认会调用下面这行，返回的文件描述符是1
	//open("/dev/stdout", O_WRONLY);
	
	char* buf = "hello123";
	int ret = write(1, buf, strlen(buf));

	return 0;
}
