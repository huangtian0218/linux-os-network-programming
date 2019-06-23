#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//非阻塞写锁
#define SET_WRFLCK(fd, whence, offset, len) \
	set_filelock(fd, F_SETLK, F_WRLCK, whence, offset, len)

//阻塞写锁
#define SET_WRFLCK_WAIT(fd, whence, offset, len) \
	set_filelock(fd, F_SETLKW, F_WRLCK, whence, offset, len)

//非阻塞读锁
#define SET_RDFLCK(fd, whence, offset, len) \
	set_filelock(fd, F_SETLK, F_RDLCK, whence, offset, len)

//阻塞读锁
#define SET_RDFLCK_WAIT(fd, whence, offset, len) \
	set_filelock(fd, F_SETLKW, F_RDLCK, whence, offset, len)

//解锁
#define SET_UNLCK(fd, whence, offset, len) \
	set_filelock(fd, F_SETLK, F_UNLCK, whence, offset, len)

//设置文件锁
void set_filelock(int fd, int waitflag, int type, int whence, int offset, int len)
{
	int ret = 0;
	struct flock flck;

	flck.l_type = F_WRLCK;
	flck.l_whence = whence;
	flck.l_start = offset;
	flck.l_len = len;

	ret = fcntl(fd, waitflag, &flck);
	if(ret == -1)
	{
		perror("Error");
		exit(-1);
	}
}

int main()
{
	int ret = -1;
	int fd = -1;
	
	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1)
	{
		perror("Error");
		return -1;
	}

	ret = fork();
	if(ret > 0)
	{
		while(1)
		{
			SET_WRFLCK_WAIT(fd, SEEK_SET, 0, 0);
			write(fd, "father ", 7);
			write(fd, "yes\n", 4);
			SET_UNLCK(fd, SEEK_SET, 0, 0);
		}
	}
	else if(ret == 0)
	{
		while(1)
		{
			SET_WRFLCK_WAIT(fd, SEEK_SET, 0, 0);
			write(fd, "son ", 4);
			write(fd, "no\n", 3);
			SET_UNLCK(fd, SEEK_SET, 0, 0);
		}
	}

	return 0;
}
