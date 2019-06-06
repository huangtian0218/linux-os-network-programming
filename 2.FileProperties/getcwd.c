#include <stdio.h>
#include <unistd.h>

int main()
{
	char buf[1024] = {0};
	getcwd(buf, sizeof(buf));
	printf("buf = %s\n", buf);

	return 0;
}
