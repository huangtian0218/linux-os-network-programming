#include <unistd.h>
#include <stdio.h>

int main()
{
	char buf[30] = {0};
	int ret = readlink("pnew", buf, sizeof(buf));
	printf("ret = %d, buf = %s\n", ret, buf);

	return 0;
}
