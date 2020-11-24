#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include "mycp.h"
#include "pthread_pool.h"
extern Pool * pool;
void * pthread_cp_regfile(void * argv)
{
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
	char temp[100];
	ssize_t size;
	while(size = read(fd, temp, 100))
	{
		if(size == -1)
			break;
		else
			write(fd1, temp, size);
	}
	close(fd);
	close(fd1);
	free(dcp);
}
void * pthread_cp(void * argv)
{
	Dcp * dcp = (Dcp *)argv;
	/* 判断目标文件是否存在并且是文件、路径是否正确
		①：如果目标目录本身已经存在，则在该目录下则新建一个文件夹
		② 不存在目标目录，创建目录，如果不能创建，说明路径错误
		创建了目录，说明创建了文件夹
	*/
	struct stat st;
	int flag = stat(dcp -> dest, &st);
	if(flag != -1 && !S_ISDIR(st.st_mode))
	{
		printf("dest not a directory\n");
		exit(EXIT_FAILURE);
	} else if(flag == -1)  
	{
		flag = mkdir(dcp -> dest, 00777);
		if(flag == -1)
		{
			perror("not create a directory");
			exit(EXIT_FAILURE);
		}
	}
	
	DIR * dir = opendir(dcp -> src);
	if(dir == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	struct dirent * sdir;
	char buf_src[2 * MAX] = "";
	char buf_dest[2 * MAX] = "";
	while(sdir = readdir(dir))
	{
		memset(buf_src, '0', MAX);
		memset(buf_dest, '0', MAX);
		if(strcmp(sdir -> d_name, ".") == 0 || strcmp(sdir -> d_name, "..") == 0)
			continue;
		if(sdir -> d_type == DT_REG)
		{
			snprintf(buf_src, 2 * MAX, "%s/%s", dcp -> src, sdir -> d_name);
			snprintf(buf_dest, 2 * MAX, "%s/%s", dcp -> dest, sdir -> d_name);
			Dcp * dcp1 = (Dcp *)malloc(sizeof(Dcp));
			strncpy(dcp1 -> src, buf_src, MAX);
			strncpy(dcp1 -> dest, buf_dest, MAX);
			enqueue(pool -> queue, pthread_cp_regfile, (void *)dcp1);
		} else if(sdir -> d_type == DT_DIR)
		{
			snprintf(buf_src, 2 * MAX, "%s/%s", dcp -> src, sdir -> d_name);
			snprintf(buf_dest, 2 * MAX, "%s/%s", dcp -> dest, sdir -> d_name);
			flag = mkdir(buf_dest, 00777);
			if(flag == -1)
			{
				perror("not create a directory");
				continue;
			}
			Dcp * dcp1 = (Dcp *)malloc(sizeof(Dcp));
			strncpy(dcp1 -> src, buf_src, MAX);
			strncpy(dcp1 -> dest, buf_dest, MAX);
			enqueue(pool -> queue, pthread_cp, (void *)dcp1);
		}
	}
	free(dcp);
}
