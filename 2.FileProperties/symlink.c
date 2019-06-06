#include <unistd.h>
#include <stdio.h>

int main()
{
	symlink("./new.txt", "pnew");

	return 0;
}
