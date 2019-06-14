#include <signal.h>
#include <stdio.h>

typedef void (*sighandler_t)(int);

void signal_fun(int signo)
{
	if(signo == SIGINT)
		printf("Catched SIGINT!!! signo = %d\n", signo);
	else if(signo == SIGQUIT)
		printf("Catched SIGQUIT!!! signo = %d\n", signo);

	//exit(-1);	//可以调用exit来正常终止
}

int main()
{
	sighandler_t ret = NULL;

	//忽略SIGINT，即Ctrl+C信号
	ret = signal(SIGINT, SIG_IGN);
	//ret返回上一次signal的处理方式，默认是SIG_DFL
	if(ret == SIG_ERR)
	{
		perror("Error:");
	}
	else if(ret == SIG_IGN)
	{
		printf("SIG_IGN\n");
	}
	else if(ret == SIG_DFL)
	{
		printf("SIG_DFL\n");
	}
	else
	{
		printf("Catched: %p\n", ret);
	}

	//Ctrl+C信号采用默认处理方式
	ret = signal(SIGINT, SIG_DFL);

	//捕获到信号自定义处理方式
	ret = signal(SIGINT, signal_fun);

	//捕获到信号自定义处理方式
	ret = signal(SIGQUIT, signal_fun);

	while(1);

	return 0;
}
