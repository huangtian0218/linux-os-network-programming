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

#define SERVER_PORT 5006
#define SERVER_IP "172.17.13.74"

typedef struct Student
{
	unsigned int num;	
	char name[50];
}stu;

static int sockfd;

void *pthread_fun(void *arg)
{
	stu s = {0};
	int ret = -1;

	while(1)
	{
		memset(&s, 0, sizeof(s));
		ret = recv(sockfd, (void *)&s, sizeof(s), 0);
		if(ret > 0)
		{
			printf("stu num: %d, stu name: %s\n", ntohl(s.num), s.name);
		}
		else if(ret == 0)
		{
			printf("recv failed!!!\n");
		}
	}
}

void signal_fun(int signo)
{
	if(signo == SIGINT)
	{
		//断开连接
		shutdown(sockfd, SHUT_RDWR);
		exit(0);
	}
}

int main()
{
	int ret = -1;

	signal(SIGINT, signal_fun);

	//创建套接字文件，并指定使用TCP协议
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("Error");
		return -1;
	}

	//调用connect主动向服务器发起三次握手
	struct sockaddr_in saddr = {0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SERVER_PORT);
	saddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	ret = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
	if(ret == -1)
	{
		perror("Error");
		return -1;
	}

	pthread_t tid;
	ret = pthread_create(&tid, NULL, pthread_fun, NULL);
	if(ret)
	{
		printf("pthread_create failed!!!\n");
		return -1;
	}

	stu s = {0};
	unsigned int tmp_num = 0;
	while(1)
	{
		memset(&s, 0, sizeof(s));	
		printf("Input num\n");
		scanf("%d", &tmp_num);
		s.num = htonl(tmp_num);
		printf("Input name\n");
		scanf("%s", s.name);

		ret = send(sockfd, (void *)&s, sizeof(s), 0);
		if(ret == -1)
		{
			perror("Error");
		}
	}

	return 0;
}
