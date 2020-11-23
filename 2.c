#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#define MAX 2;
int main()
{
	DIR * dir = opendir(".");
	if(dir == NULL)
	{
		//perror("opendir first");
		int fd = mkdir("test", 00777);
		if(fd == -1)
		{
			perror("mkdir test");
			exit(EXIT_FAILURE);
		}
		dir = opendir("test");
		if(dir == NULL)
		{
			perror("opendir second");
			exit(EXIT_FAILURE);
		}
	}
	struct dirent * sdir;
	while(sdir = readdir(dir))
	{
		printf("%s\n", sdir -> d_name);
	}
}
