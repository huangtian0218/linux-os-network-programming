#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd = open(argv[1], O_RDONLY);
	struct stat s = {0};
	fstat(fd, &s);

	//文件类型
	char mode = 0;
	if(S_ISLNK(s.st_mode))
		mode = 'l';
	else if(S_ISREG(s.st_mode))
		mode = '-';
	else if(S_ISDIR(s.st_mode))
		mode = 'd';
	else if(S_ISCHR(s.st_mode))
		mode = 'c';
	else if(S_ISBLK(s.st_mode))
		mode = 'b';
	else if(S_ISFIFO(s.st_mode))
		mode = 'p';
	else if(S_ISSOCK(s.st_mode))
		mode = 's';

	//文件权限
	char perm[10] = {0};
	char base[] = "rwxrwxrwx";
	int i = 0;
	for(i = 0; i < 9; i++)
	{
		if(s.st_mode & (1<<(8-i)))
			perm[i] = base[i];
		else
			perm[i] = '-';
	}
	printf("%c%s %ld %d %d %ld %ld %s\n", mode, perm, s.st_nlink, s.st_uid, s.st_gid, s.st_size, s.st_atime, argv[1]);

	return 0;
}
