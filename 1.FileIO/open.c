#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd = 0;

	//O_RDONLY: 只读
	//O_WRONLY: 只写
	//O_RDWR: 读写
	//O_TRUNC: 清空
	//O_APPEND: 追加
	fd = open("./1.txt", O_RDWR);
	
	//O_CREAT: 打开时不存在则创建
	//O_EXCL: 和O_CREAT搭配使用，打开文件时之前存在报错，保证每次open的都是新文件
	//open如果有第三个参数表示新创建文件的默认权限
	//fd = open("./1.txt", O_RDWR | O_CREAT, 0664);

	if(-1 == fd)
	{
		printf("open failed!\n");
		return -1;
	}

	write(fd, (void *)"hello", 3);

	//移动光标至文件头部
	lseek(fd, 0, SEEK_SET);

	char buf[30] = {0};
	read(fd, buf, 30);
	printf("%s\n", buf);

	close(fd);

	return 0;
}
