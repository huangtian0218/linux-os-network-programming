#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_fun(int signo)
{
	sigset_t set;
	printf("hello\n");
	//将变量set的64位屏蔽字全部设置为0
	sigemptyset(&set);
	//将变量set的64位屏蔽字中的SIGINT设置为1，其它位不变
	sigaddset(&set, SIGINT);
	//使用设置好的set去修改信号屏蔽字，第三个参数为NULL表示不保存之前的值
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	sleep(3);
	printf("world\n");
}

int main()
{
	pid_t ret = 0;
	
	signal(SIGINT, signal_fun);

	while(1);

	return 0;
}
