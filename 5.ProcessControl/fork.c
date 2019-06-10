#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("before fork...\n");
	pid_t ret = fork();
	if(ret > 0)
	{
		printf("parent...\n");
	}

	if(ret == 0)
	{
		printf("child...\n");
	}

	printf("%d: ret = %d\n", getpid(), ret);

	while(1);

	return 0;
}
