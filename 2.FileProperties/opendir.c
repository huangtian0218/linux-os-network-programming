#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
	DIR* dir = NULL;
	dir = opendir("/home/lichen/");
	if(NULL == dir)
	{
		perror("Error");
		return -1;
	}

	return 0;
}
