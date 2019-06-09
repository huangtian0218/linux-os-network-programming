#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main()
{
	putenv("ZZ=aaaaaaaaaaaaaaaaa");

	unsetenv("ZZ");

	int i = 0;
	for(i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}

	return 0;
}
