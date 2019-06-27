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

#define SERVER_PORT 5002
#define SERVER_IP "172.17.13.74"

static int sockfd;
struct sockaddr_in peer_addr = {0};

void *pthread_fun(void *arg)
{
	int ret = -1;
	int size = sizeof(peer_addr);
	char buf[1024] = {0};

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ret = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&peer_addr, &size);
		if(ret == -1)
		{
			printf("recvfrom failed!!!\n");
		}
		else if(ret > 0)
		{
			printf("peer_ip: %s, peer_port: %d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
			printf("%s\n", buf);
		}
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	int ret = -1;
	char buf[1024] = {0};

	if(argc < 3)
	{
		printf("error: too few arguments to function 'main'");
		return -1;
	}

	//创建套接字文件，使用UDP协议
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		printf("socket failed!!!\n");
		return -1;
	}

	//调用bind绑定固定的ip和端口
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == -1)
	{
		printf("bind failed!!!\n");
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
		//设置对方的ip和端口
		peer_addr.sin_family = AF_INET;
		peer_addr.sin_port = htons(atoi(argv[2]));
		peer_addr.sin_addr.s_addr = inet_addr(argv[1]);

		memset(buf, 0, sizeof(buf));
		scanf("%s", buf);
		ret = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&peer_addr, sizeof(peer_addr));
		if(ret == -1)
		{
			printf("sendto failed\n");
		}
	}

	return 0;
}
