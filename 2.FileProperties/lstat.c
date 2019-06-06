#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	//lstat与stat的区别是当操作对象是链接文件时，stat会获取链接文件指向的真正文件的属性
	//而lstat会获取文件本身的属性
	struct stat s = {0};
	lstat(argv[1], &s);

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

	if(mode == 'l')
	{
		char buf[30] = {0};
		readlink(argv[1], buf, sizeof(buf));
		printf("%c%s %ld %d %d %ld %ld %s --> %s\n", mode, perm, s.st_nlink, s.st_uid, s.st_gid, s.st_size, s.st_atime, argv[1], buf);
	}
	else
	{
		printf("%c%s %ld %d %d %ld %ld %s\n", mode, perm, s.st_nlink, s.st_uid, s.st_gid, s.st_size, s.st_atime, argv[1]);
	}

	return 0;
}
