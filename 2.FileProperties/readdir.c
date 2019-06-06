#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int main()
{
	DIR* dir = NULL;
	dir = opendir("/home/lichen/");
	if(NULL == dir)
	{
		perror("Error");
		return -1;
	}

	while(1)
	{
		struct dirent* dirp = readdir(dir);
		if(dirp == NULL && errno != 0 )
		{
			perror("Error");
			return -1;
		}

		if(dirp == NULL && errno == 0)
			break;

		printf("inode = %ld, filename = %s\n", dirp->d_ino, dirp->d_name);	
	}

	return 0;
}
