#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

#define PTH_NUMS 100

static int sockfd;

typedef struct pthread_arg
{
	pthread_t tid;
	int cfd;
}ptharg;

void *pthread_fun(void *arg)
{
	int ret = -1;
	char buf[1024] = {0};

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ret = recv(sockfd, buf, sizeof(buf), 0);
		if(ret == -1)
		{
			printf("recv failed!!!\n");
		}
		else if(ret > 0)
		{
			printf("server: %s\n", buf);
		}
	}

	return NULL;
}

int main()
{
	int ret = -1;
	struct sockaddr_in saddr;
	char buf[1024] = {0};
	pthread_t tid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("Error");
		return -1;
	}
	
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5006);
	saddr.sin_addr.s_addr = inet_addr("172.17.13.74");
	ret = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
	if(ret == -1)
	{
		printf("connect failed!!!\n");
		return -1;
	}

	ret = pthread_create(&tid, NULL, pthread_fun, NULL);
	if(ret)
	{
		printf("pthread_create failed!!!\n");
	}

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		scanf("%s", buf);
		ret = send(sockfd, buf, sizeof(buf), 0);
		if(ret == -1)
		{
			printf("send failed\n");
		}
	}

	return 0;
}
