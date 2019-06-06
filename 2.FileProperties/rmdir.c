#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	//只能删除空目录，此时可以使用remove函数
	int ret = rmdir("./test");
	if(-1 == ret)
	{
		perror("Error");
		return -1;
	}

	return 0;
}
