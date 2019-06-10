#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("%u\n", getgid());

	return 0;
}

