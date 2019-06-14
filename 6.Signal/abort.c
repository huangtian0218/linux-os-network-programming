#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	//自杀信号，给自己发送一个SIGABRT信号
	abort();

	while(1);

	return 0;
}
