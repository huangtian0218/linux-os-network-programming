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

static int sockfd;
struct sockaddr_un peer_addr;

void *pthread_fun(void *arg)
{
	int ret = -1;
	char buf[1024] = {0};
	int size = sizeof(peer_addr);

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
			printf("buf = %s\n", buf);
		}
	}

	return NULL;
}

void signal_fun(int signo)
{
	if(signo == SIGINT)
	{
		remove("./socket_file_1");
		exit(-1);
	}
}

int main(int argc, char *argv[])
{
	int ret = -1;
	char buf[1024] = {0};
	struct sockaddr_un addr = {0};

	signal(SIGINT, signal_fun);

	if(argc < 2)
	{
		printf("too few paramter of 'main'\n");
		return -1;
	}

	sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("Error");
		return -1;
	}

	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path), "./socket_file_1");
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
		peer_addr.sun_family = AF_UNIX;
		snprintf(peer_addr.sun_path, sizeof(peer_addr.sun_path), "%s", argv[1]);

		memset(buf, 0, sizeof(buf));
		scanf("%s", buf);
		
		ret = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&peer_addr, sizeof(peer_addr));
		if(ret == -1)
		{
			printf("sendto failed!!!\n");
		}
	}

	return 0;
}
