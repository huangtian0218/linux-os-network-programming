#include <stdio.h>
#include <unistd.h>

int main()
{
	//5秒后进程终止
	alarm(5);

	while(1);

	return 0;
}
