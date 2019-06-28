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
	long cfd = (long)arg;
	int ret = -1;
	char buf[1024] = {0};

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ret = recv(cfd, buf, sizeof(buf), 0);
		if(ret == -1)
		{
			printf("recv failed!!!\n");
		}
		else if(ret > 0)
		{
			printf("client: %s\n", buf);
			ret = send(cfd, "recv ok\n", strlen("recv OK!\n"), 0);
			if(ret == -1)
			{
				printf("send failed!!!\n");
			}
		}
	}

	return NULL;
}

int main()
{
	int ret = -1;
	long cfd = -1;
	struct sockaddr_in addr;
	pthread_t tid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("Error");
		return -1;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5006);
	addr.sin_addr.s_addr = inet_addr("172.17.13.74");
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == -1)
	{
		printf("bind failed!!!\n");
		return -1;
	}

	ret = listen(sockfd, 3);
	if(ret == -1)
	{
		perror("Error");
		return -1;
	}

	while(1)
	{
		cfd = accept(sockfd, NULL, NULL);
		if(cfd == -1)
		{
			printf("accept failed!!!\n");
		}

		ret = pthread_create(&tid, NULL, pthread_fun, (void *)cfd);
		if(ret)
		{
			printf("pthread_create failed!!!\n");
		}
	}

	return 0;
}
