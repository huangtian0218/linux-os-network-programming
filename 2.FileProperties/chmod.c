#include <sys/stat.h>
#include <stdio.h>

int main()
{
	chmod("./test", 0777);

	return 0;
}
