#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	mkdir("./test", 0755);

	return 0;
}
