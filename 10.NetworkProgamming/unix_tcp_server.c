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

static int cfd = -1;

void *pthread_fun(void *arg)
{
	int ret = -1;
	char buf[1024] = {0};

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(cfd, buf, sizeof(buf));
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

void signal_fun(int signo)
{
	if(SIGINT == signo)
	{
		remove("./f_socket");
		exit(-1);
	}
}

int main()
{
	int sockfd = -1;
	int ret = -1;
	char buf[1024] = {0};
	struct sockaddr_un addr = {0};

	signal(SIGINT, signal_fun);

	//创建域套接字
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("Error");
		return -1;
	}

	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path), "./f_socket");
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));	
	if(ret == -1)
	{
		printf("bind failed!!!\n");
		return -1;
	}

	ret = listen(sockfd, 3);
	if(ret == -1)
	{
		printf("listen failed!!!\n");
		return -1;
	}

	cfd = accept(sockfd, NULL, NULL);
	if(cfd == -1)
	{
		printf("accept failed!!!\n");
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

		ret = write(cfd, buf, sizeof(buf));
		if(ret == -1)
		{
			printf("write failed!!!\n");
		}
	}

	return 0;
}
