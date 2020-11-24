#include <stdio.h>
 #include <sys/types.h>      
  #include <dirent.h>
#include <stdlib.h>
  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
int main()
{
	struct stat st;
	int id = stat("test", &st);
	if(id == -1)
	{
		perror("无此文件");
		int fd = mkdir("test", 00777);
		if(fd == -1)
		{
			perror("");
		}
		return 0;
	}	
	/*if(st.st_mode & S_IFMT == S_IFREG)
	{
		printf("是目录文件\n");
	}
	else if(st.st_mode & S_IFMT == S_IFREG) 
	
		printf("时普通文件\n");
	else
		printf("非普通文件或目录文件\n");
	*/
}
