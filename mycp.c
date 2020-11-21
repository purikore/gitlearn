#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

typedef cp_directory
{
	char src[255];
	char dest[255];
}Dcp;
void * pthread_cp(void * argv)
{
	Dcp * dcp = (Dcp *)malloc(sizeof(Dcp));
	DIR * dir = opendir("test");
	if(dir == NULL)
	{
		
	}
}
int main(int argc, char * argv[])
{
	
	return 0;
}
