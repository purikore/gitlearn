 #include <sys/types.h>      
  #include <sys/stat.h>    
#include <fcntl.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>
int main()
{
	//FILE * file = fopen("/mnt/d/linux_share/第二阶段/day38线程/abc/test.c", "a+");
	//if(file == NULL)
	//{
	//	perror("");
	//}
	
	char * dirc = strdup("/////etc/////fdasdf");
	char * p = basename(dirc);
	//printf("%s\n", dirc);
	printf("%s\n", p);
}
