#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct pthread_arg
{
	pthread_t tid;
	int pthno;
	int fd;
}ptharg;

void *pthread_fun(void *arg)
{
	int fd = ((ptharg *)arg)->fd;

	printf("pthno = %d, tid = %lu\n", ((ptharg *)arg)->pthno, ((ptharg *)arg)->tid);
	//线程获取自己tid的另一种方式
	printf("Another get tid = %lu\n", pthread_self());

	while(1)
	{
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
	}

	return NULL;
}

int main()
{
	int i = 0;
	int ret = 0;
	int fd = -1;
	ptharg ptharg[2];

	fd = open("./file", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if(fd == -1)
	{
		printf("%s[%d]open file failed!!!", __FUNCTION__, __LINE__);
		return -1;
	}

	//通过循环创建两个次线程
	for(i = 0; i < 2; i++)
	{
		ptharg[i].fd = fd;
		ptharg[i].pthno = i;
		ret = pthread_create(&ptharg[i].tid, NULL, pthread_fun, (void *)&ptharg[i]);
		if(ret != 0)
		{
			printf("%s[%d]pthread_create failed!!!", __FUNCTION__, __LINE__);
			return -1;
		}
	}

	while(1)
	{
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
	}

	return 0;
}
