#include <stdio.h>

int main()
{
	FILE* fp = fopen("./haha", "r+");	
	if(!fp)
	{
		perror("Error");
		return -1;
	}

	fclose(fp);

	return 0;
}
