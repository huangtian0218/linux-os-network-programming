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

#define SEM_NUMS 3	//信号量数量

static pthread_attr_t attr;	//存放线程属性
static pthread_t tid[2];
static sem_t sem[SEM_NUMS];

void *pthread_fun1(void *arg)
{
	while(1)
	{
		sem_wait(&sem[0]);	//P操作
		printf("second1 pthread\n");
		sleep(1);
		sem_post(&sem[1]);	//V操作
	}
	
	return NULL;
}

void *pthread_fun2(void *arg)
{
	while(1)
	{
		sem_wait(&sem[1]);	//P操作
		printf("second2 pthread\n");
		sleep(1);
		sem_post(&sem[2]);	//V操作
	}

	return NULL;
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
	for(i = 0; i < SEM_NUMS; i++)
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
	void *(*pthread_fun[])(void *) = {pthread_fun1, pthread_fun2};

	//注册进程退出处理函数
	atexit(process_exit_deal);

	//初始化信号量
	for(i = 0; i < SEM_NUMS; i++)
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
		ret = pthread_create(&tid[i], &attr, pthread_fun[i], NULL);
		if(ret != 0)
		{
			printf("%s[%d]pthread_create failed!!!", __FUNCTION__, __LINE__);
			return -1;
		}
	}

	while(1)
	{
		sem_wait(&sem[2]);	//P操作
		printf("master pthread!\n");
		sleep(1);
		sem_post(&sem[0]);	//V操作
	}

	return 0;
}
