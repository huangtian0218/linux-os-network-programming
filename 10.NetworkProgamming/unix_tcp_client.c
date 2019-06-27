#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

static int sockfd = -1;

void *pthread_fun(void *arg)
{
	int ret = -1;
	char buf[1024] = {0};

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(sockfd, buf, sizeof(buf));
#if 0
		if(ret == -1)
		{
			printf("read failed!!!\n");
		}
		else if(ret > 0)
		{
			printf("buf = %s\n", buf);
		}
#endif
		if(ret > 0)
		{
			printf("buf = %s\n", buf);
		}
	}

	return NULL;
}

int main()
{
	int ret = -1;
	char buf[1024] = {0};
	struct sockaddr_un saddr = {0};

	//创建域套接字
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("Error");
		return -1;
	}

	saddr.sun_family = AF_UNIX;
	snprintf(saddr.sun_path, sizeof(saddr.sun_path), "./f_socket");

	ret = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
	if(ret == -1)
	{
		printf("connect failed!!!\n");
		return -1;
	}

	pthread_t tid;
	ret = pthread_create(&tid, NULL, pthread_fun, NULL);
	if(ret)
	{
		printf("pthread_create failed!!!\n");
		return -1;
	}

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		scanf("%s", buf);

		ret = write(sockfd, buf, sizeof(buf));
		if(ret == -1)
		{
			printf("write failed!!!\n");
		}
	}

	return 0;
}
