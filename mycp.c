#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#define MAX 255
typedef struct cp_directory
{
	char src[MAX];
	char dest[MAX];
}Dcp;
void * pthread_cp_regfile(void * argv)
{
	sleep(5);
	Dcp * dcp = (Dcp *)argv;
	int fd = open(dcp -> src, O_RDONLY);
	if(fd == -1)
	{
		perror("open src");
		exit(EXIT_FAILURE);
	}
	int fd1 = open(dcp -> dest, O_RDWR | O_TRUNC | O_CREAT, 00777);
	if(fd1 == -1)
	{
		perror("open dest");
		exit(EXIT_FAILURE);
	}
	char temp[5];
	ssize_t size;
	while(size = read(fd, temp, 5))
	{
		if(size == -1)
			break;
		else
			write(fd1, temp, size);
	}
	close(fd);
	close(fd1);
	printf("子线程结束\n");
	pthread_exit(NULL);
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
			exit(EXIT_FAILURE);
		}
	}
	
}
int main(int argc, char * argv[])
{
	
	/*pthread_t * pid_arr[3];
	pthread_t pid;
	for(int i = 2; i < 5; i++)
	{
		Dcp * dcp = (Dcp *)malloc(sizeof(Dcp));
		strncpy(dcp -> src, argv[1], MAX);
		strncpy(dcp -> dest, argv[i], MAX);
		pid_arr[i - 2] = &pid;
		pthread_create(&pid, NULL, pthread_cp_regfile, (void *)dcp);
		//pthread_join(pid, NULL);
	}
	for(int i = 0; i < 3; i++)
	{
		pthread_join(*(pid_arr[i]), NULL);
		printf("等到第个线程\n");
	}*/
	struct stat st;
	int flag = stat(argv[2], &st);
	/* 判断目标文件是否存在并且是文件、路径是否正确
		①：如果目标目录本身已经存在，则在该目录下则新建一个文件夹
		② 不存在目标目录，创建目录，如果不能创建，说明路径错误
		创建了目录，说明创建了文件夹
	*/
	if(flag != -1 && !S_ISDIR(st.st_mode))
	{
		printf("dest not a directory\n");
		exit(EXIT_FAILURE);
	} else if(flag == -1)
	{
		flag = mkdir(argv[2], 00777);
		if(flag == -1)
		{
			perror("not create a directory");
			exit(EXIT_FAILURE);
		}
	}
	/*判断源文件*/
	flag = stat(argv[1], &st);
	if(flag == -1)
	{
		perror("src");
		exit(EXIT_FAILURE);
	}
	else if()
	return 0;
}
