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
	int exitflag;
};

static struct pthread_arg ptharg[2];
static pthread_attr_t attr;	//存放线程属性

void *pthread_fun(void *arg)
{
	int fd = ((struct pthread_arg *)arg)->fd;

	//分离次线程，让次线程结束后自动回收资源，但是无法获取次线程结束时的返回值
	//pthread_detach(pthread_self());
		
	printf("pthno = %d, tid = %lu\n", ((struct pthread_arg *)arg)->pthno, ((struct pthread_arg *)arg)->tid);

	while(1)
	{
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);

		if(((struct pthread_arg *)arg)->exitflag == 1)
			break;
	}

	pthread_exit((void *)5);
}

void signal_fun(int signo)
{
	if(SIGALRM == signo)
	{
		int i = 0;
		for(i = 0; i < 2; i++)
		{
			ptharg[i].exitflag = 1;
			//pthread_cancel(ptharg[i].tid);
		}
	}
	else if(SIGINT == signo)
	{
		int ret = 0;
		ret = pthread_attr_destroy(&attr);
		if(ret)
		{
			printf("pthread_attr_destroy failed!!!\n");
		}

		exit(0);
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

	//初始化线程属性attr
	ret = pthread_attr_init(&attr);
	if(ret)
	{
		printf("pthread_attr_init failed!!!\n");
		return -1;
	}

	//设置分离属性
	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(ret)
	{
		printf("pthread_attr_setdetachstate failed!!!\n");
		return -1;
	}

	//通过循环创建两个次线程
	for(i = 0; i < 2; i++)
	{
		ptharg[i].fd = fd;
		ptharg[i].pthno = i;
		ptharg[i].exitflag = 0;
		ret = pthread_create(&ptharg[i].tid, &attr, pthread_fun, (void *)&ptharg[i]);
		if(ret != 0)
		{
			printf("%s[%d]pthread_create failed!!!", __FUNCTION__, __LINE__);
			return -1;
		}
	}

	//定时3秒，时间到后取消次线程
	signal(SIGALRM, signal_fun);
	signal(SIGINT, signal_fun);
	alarm(3);

	while(1)
	{
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
	}

	return 0;
}
