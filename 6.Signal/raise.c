#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	//向当前进程发送一个信号
	raise(SIGUSR1);

	return 0;
}
