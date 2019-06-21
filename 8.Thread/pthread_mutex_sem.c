#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <semaphore.h>

struct pthread_arg
{
	pthread_t tid;
	int pthno;
	int fd;
	int exitflag;
};

static struct pthread_arg ptharg[2];
static pthread_attr_t attr;	//存放线程属性
static sem_t sem[1];

void *pthread_fun(void *arg)
{
	int fd = ((struct pthread_arg *)arg)->fd;

	printf("pthno = %d, tid = %lu\n", ((struct pthread_arg *)arg)->pthno, ((struct pthread_arg *)arg)->tid);

	while(1)
	{
		sem_wait(&sem[0]);	//P操作
		write(fd, "second ", 7);
		write(fd, "print\n", 6);
		sem_post(&sem[0]);	//V操作

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
		exit(0);
	}
}

void process_exit_deal()
{
	int ret = 0;
	int i = 0;

	//销毁线程属性设置
	ret = pthread_attr_destroy(&attr);
	if(ret)
	{
		printf("pthread_attr_destroy failed!!!\n");
	}

	//销毁线程信号量集合
	for(i = 0; i < 1; i++)
	{
		ret = sem_destroy(&sem[i]);

		if(ret)
			printf("sem_destroy sem[%d] failed\n", i);
	}

	printf("process exit!\n");
}

int main()
{
	int i = 0;
	int ret = 0;
	int fd = -1;

	//注册进程退出处理函数
	atexit(process_exit_deal);

	fd = open("./file", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if(fd == -1)
	{
		printf("%s[%d]open file failed!!!", __FUNCTION__, __LINE__);
		return -1;
	}

	//初始化信号量，由于只有一个信号量，这个for循环可以不写
	for(i = 0; i < 1; i++)
	{
		//第二个参数表示给线程使用，!0则给进程用，第三个参数表示初始化的值
		if(i == 0)
			ret = sem_init(&sem[i], 0, 1);
		else
			ret = sem_init(&sem[i], 0, 0);

		if(ret)
			printf("sem_init sem[%d] failed\n", i);
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
		sem_wait(&sem[0]);	//P操作
		write(fd, "master ", 7);
		write(fd, "print\n", 6);
		sem_post(&sem[0]);	//V操作
	}

	return 0;
}
