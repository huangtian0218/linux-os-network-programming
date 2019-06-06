#include <unistd.h>
#include <stdio.h>

int main()
{
	link("./stat.c", "./test");

	return 0;
}
