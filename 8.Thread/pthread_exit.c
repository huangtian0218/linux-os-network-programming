#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

struct pthread_arg
{
	pthread_t tid;
	int pthno;
	int fd;
};

static struct pthread_arg ptharg[2];

void *pthread_fun(void *arg)
{
	int fd = ((struct pthread_arg *)arg)->fd;

	printf("pthno = %d, tid = %lu\n", ((struct pthread_arg *)arg)->pthno, ((struct pthread_arg *)arg)->tid);

	while(1)
	{
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
		printf("#####\n");
	}

	pthread_exit(NULL);
}

void signal_fun(int signo)
{
	if(SIGALRM == signo)
	{
		int i = 0;
		for(i = 0; i < 2; i++)
		{
			pthread_cancel(ptharg[i].tid);
		}
	}
}

int main()
{
	int i = 0;
	int ret = 0;
	int fd = -1;

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

	//定时5秒，时间到后取消次线程
	signal(SIGALRM, signal_fun);
	alarm(5);

	while(1)
	{
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
	}

	return 0;
}
