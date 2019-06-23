#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

int main()
{
	int ret = -1;

	ret = fork();
	if(ret > 0)
	{
		int fd = -1;
		//flock加文件锁，每个进程或者线程必须自己open，得到属于自己的fd，此时需要添加O_APPEND
		fd = open("./file", O_RDWR|O_CREAT|O_TRUNC|O_APPEND, 0664);
		if(fd == -1)
		{
			perror("Error");
			return -1;
		}

		while(1)
		{
			flock(fd, LOCK_EX);	//加锁
			write(fd, "father ", 7);
			write(fd, "yes\n", 4);
			flock(fd, LOCK_UN); //解锁
		}
	}
	else if(ret == 0)
	{
		int fd = -1;
		//flock加文件锁，每个进程或者线程必须自己open，得到属于自己的fd，此时需要添加O_APPEND
		fd = open("./file", O_RDWR|O_CREAT|O_TRUNC|O_APPEND, 0664);
		if(fd == -1)
		{
			perror("Error");
			return -1;
		}

		while(1)
		{
			flock(fd, LOCK_EX);
			write(fd, "son ", 4);
			write(fd, "no\n", 3);
			flock(fd, LOCK_UN);
		}
	}

	return 0;
}
