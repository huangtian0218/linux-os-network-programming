#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main()
{
	putenv("ZZ=aaaaaaaaaaaaaaaaa");

	setenv("ZZ", "************************", !0);

	int i = 0;
	for(i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}

	return 0;
}
