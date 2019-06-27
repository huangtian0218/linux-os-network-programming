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

static int cfd = -1;		//通信描述符

//次线程接收客户端的数据
void *pthread_fun(void *pth_arg)
{
	int ret = 0;
	stu s = {0};
	while(1)
	{
		memset(&s, 0, sizeof(s));
		ret = recv(cfd, &s, sizeof(s), 0);
		if(ret == -1)
		{
			perror("Error");
		}
		else if(ret > 0)
		{
			printf("s.num = %d, s.name = %s\n", ntohl(s.num), s.name);
		}
	}

	return NULL;
}

void signal_fun(int signo)
{
	if(signo == SIGINT)
	{
		//断开连接，一次性关闭读和写
		//close(cfd);

		//断开连接
		shutdown(cfd, SHUT_RDWR);
		cfd = -1;
		exit(-1);
	}
}

int main()
{
	int sockfd = -1;	//主动描述符
	int ret = -1;		//被动描述符

	signal(SIGINT, signal_fun);	

	//创建使用TCP协议的套接字文件
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("Error");
		return -1;
	}

	//调用Bind绑定套接字文件/服务器ip/服务器端口
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SERVER_PORT);	//htons将主机端序转换成网络大端序
	saddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	ret = bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
	if(ret == -1)
	{
		perror("Error");
		return -1;
	}

	//将套接字文件描述符，从主动描述符转换成被动文件描述符，被动监听客户的连接
	//第二个参数表示正在连接但是还没连接成功的客户的队列大小，一般设置成2或3
	ret = listen(sockfd, 3);
	if(ret == -1)
	{
		perror("Error");
		return -1;
	}

	//调用accept被动监听客户的连接
	struct sockaddr_in caddr = {0};
	int caddr_size = sizeof(caddr);
	cfd = accept(sockfd, (struct sockaddr *)&caddr, &caddr_size);
	if(cfd == -1)
	{
		perror("error");
		return -1;
	}

	//打印客户端的ip和port，进行端序转换
	printf("client_port = %d, client_ip = %s\n", ntohs(caddr.sin_port), inet_ntoa(caddr.sin_addr));

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
		printf("Input num:\n");
		scanf("%d", &tmp_num);
		s.num = htonl(tmp_num);

		printf("Input name:\n");
		scanf("%s", s.name);

		ret = send(cfd, (void *)&s, sizeof(s), 0);
		if(ret == -1)
		{
			printf("send failed!!!\n");
		}
	}

	return 0;
}
