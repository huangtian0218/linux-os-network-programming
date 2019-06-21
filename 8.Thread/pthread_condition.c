#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int va;
static pthread_cond_t cond;	//定义条件变量
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;	//初始化快锁

void *pthread_fun(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		//mutex传递给该函数，防止线程休眠后没有解锁，导致其它线程用这个互斥锁时加锁失败
		pthread_cond_wait(&cond, &mutex);
		printf("va = %d\n", va);
		va = 0;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

void signal_fun(int signo)
{
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);

	exit(0);
}

int main()
{
	int ret = 0;
	pthread_t tid;

	signal(SIGINT, signal_fun);

	ret = pthread_cond_init(&cond, NULL);	
	if(ret)
	{
		printf("pthread_cond_init failed!\n");
		return -1;
	}

	ret = pthread_create(&tid, NULL, pthread_fun, NULL);
	if(ret)
	{
		printf("pthread_create failed!\n");
		return -1;
	}

	while(1)
	{
		pthread_mutex_lock(&mutex);
		va++;
		if(va == 3)
		{
			pthread_cond_signal(&cond);
		}
		pthread_mutex_unlock(&mutex);

		sleep(1);
	}

	return 0;
}
