#include <stdlib.h>
#include <stdio.h>

void fun(void)
{
	printf("process...\n");
}

int main()
{
	//注册进程终止处理函数，函数正常终止时调用，异常终止不会调用
	atexit(fun);

	printf("finish...\n");

	return 0;
}
