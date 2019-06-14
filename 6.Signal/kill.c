#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	kill(getpid(), SIGUSR1);

	return 0;
}
