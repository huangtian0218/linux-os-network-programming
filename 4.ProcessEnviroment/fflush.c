#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("==================");
	//fflush(stdout);	//刷新标准输出库缓存
	//fclose(stdout);	//fclose会自动调用fflush刷新缓存，并关闭文件
	//exit(0);	//exit会自动调用fclose关闭所有的标准IO
	_exit(0);	//_exit不会调用flose
	while(1);

	return 0;
}
