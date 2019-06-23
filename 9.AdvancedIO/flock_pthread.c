#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <pthread.h>

void *pthread_fun(void *arg)
{
	int fd = -1;

	fd = open("./file", O_WRONLY|O_CREAT|O_TRUNC|O_APPEND, 0664);
	if(fd == -1)
	{
		perror("Error");
		return NULL;
	}

	while(1)
	{
		flock(fd, LOCK_EX);
		write(fd, "second ", 7);
		write(fd, "print\n", 6);
		flock(fd, LOCK_UN);
	}

	return NULL;
}

int main()
{
	int ret = -1;
	int fd = -1;
	pthread_t tid;

	fd = open("./file", O_WRONLY|O_CREAT|O_TRUNC|O_APPEND, 0664);
	if(fd == -1)
	{
		perror("Error");
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
		flock(fd, LOCK_EX);
		write(fd, "main ", 5);
		write(fd, "print\n", 6);
		flock(fd, LOCK_UN);
	}

	return 0;
}
