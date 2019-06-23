#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int srcfd = -1;
	int dstfd = -1;
	void *srcaddr = NULL;
	void *dstaddr = NULL;

	//打开源文件
	srcfd = open("./file", O_RDONLY);
	if(srcfd == -1)
	{
		perror("Error");
		return -1;
	}

	//打开目标文件
	dstfd = open("./file.bak", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(dstfd == -1)
	{
		perror("Error");
		return -1;
	}

	//获取源文件的属性
	struct stat src_stat = {0};
	fstat(srcfd, &src_stat);

	//mmap映射源文件
	//第一个参数NULL表示由mmap函数确定映射地址，
	//第二个参数表示映射文件的字节数
	//第三个参数PROT_READ表示读该文件
	//第四个参数MAP_SHARED表示立即更新该文件
	//第五个参数是文件描述符
	//第六个参数0表示映射整个文件
	srcaddr = mmap(NULL, src_stat.st_size, PROT_READ, MAP_SHARED, srcfd, 0);	
	if(srcaddr == (void *)-1)
	{
		printf("mmap failed!\n");
		return -1;
	}

	//截断目标文件，防止该文件大小为0导致mmap失败
	ftruncate(dstfd, src_stat.st_size);

	//mmap映射目标文件
	dstaddr = mmap(NULL, src_stat.st_size, PROT_WRITE, MAP_SHARED, dstfd, 0);
	if(dstaddr == (void *)-1)
	{
		printf("mmap failed!\n");
		return -1;
	}

	//源文件数据复制到目标文件中
	memmove(dstaddr, srcaddr, src_stat.st_size);

	//取消映射
	munmap(srcaddr, src_stat.st_size);
	munmap(dstaddr, src_stat.st_size);

	return 0;
}

