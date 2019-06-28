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

extern char *environ[];

int main()
{
	int ret = -1;
	int sockfd = -1;
	int cfd = -1;
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

		ret = fork();
		if(ret > 0)
		{
			close(cfd);
		}
		else if(ret == 0)
		{
			char buf[10] = {0};
			snprintf(buf, sizeof(buf), "%d", cfd);
			char *argv[] = {buf, NULL};
			//执行新程序，负责与客户端的通信
			ret = execve("./new_pro", argv, environ);
			if(ret == -1)
			{
				printf("execve failed!!!\n");
			}
		}
	}

	return 0;
}
