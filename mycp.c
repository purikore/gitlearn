#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

typedef cp_directory
{
	char src[255];
	char dest[255];
}Dcp;
void * pthread_cp_regfile(void * agrv)
{
	Dcp * dcp = (Dcp *)malloc(sizeof(Dcp));
	int fd = open(dcp -> src, O_RDONLY);
	if(fd == -1)
	{
		perror("open src");
		exit(EXIT_FAILURE);
	}
	int fd1 = open(dcp -> dest, O_RDWR | O_TRUNC | O_CREATE, 00777);
	{
		perror("open dest");
		exit(EXIT_FAILURE);
	}


	
	close(fd);
	close(fd1);
}
void * pthread_cp(void * argv)
{
	int fd;
	Dcp * dcp = (Dcp *)malloc(sizeof(Dcp));
	DIR * dir = opendir(dcp -> dest);
	if(dir == NULL)
	{
		fd = mkdir(dcp -> dest, 00777);
		if(fd == -1)
		{
			perror("mkdir dest");
			exit(EXIT_FAILURE);
		}
		dir = opendir(dcp -> dest);
		if(dir == NULL)
		{
			perror("opendir dest");
			eixt(EXIT_FAILURE);
		}
	}
	
}
int main(int argc, char * argv[])
{
	
	return 0;
}
