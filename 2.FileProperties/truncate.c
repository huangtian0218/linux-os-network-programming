#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	//截断该文件成3个字符
	truncate("./tmp.txt", 3);

	//利用truncate创建空洞文件，使用ls -l查看文件大小为8000字节，但是用du命令查看则为0
	//truncate("./tmp.txt", 8000);

	return 0;
}
