#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("%u\n", getpid());

	return 0;
}

