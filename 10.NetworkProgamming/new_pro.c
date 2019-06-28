#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char *argv[])
{
	printf("start...\n");
	int cfd = atoi(argv[1]);
	char buf[1024] = {0};
	int ret = -1;

	printf("cfd = %d\n", cfd);
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
			ret = send(cfd, "recv ok!", strlen("recv ok!"), 0);
			if(ret == -1)
			{
				printf("send failed!!!\n");
			}
		}
	}

	return 0;
}
