#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("before pause...\n");

	//进入休眠
	pause();
	printf("after pause...\n");

	while(1);

	return 0;
}
