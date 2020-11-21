#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_rwlock_t rwlock;
int read_num = 0;
int write_num = 0;
void * reader(void * argv)
{
	while(1)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf("读的次数为%d\n", ++read_num);
		pthread_rwlock_unlock(&rwlock);
		//usleep(1000);
	}
	pthread_exit(NULL);
}

void * writer(void * argv)
{
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		//data++;
		printf("写的次数为%d\n", ++write_num);
		pthread_rwlock_unlock(&rwlock);
		//usleep(1000);
	}
	pthread_exit(NULL);
}
int main()
{
	pthread_rwlockattr_t attr;
	pthread_rwlockattr_init(&attr);
	pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
	int flag = pthread_rwlock_init(&rwlock, NULL);
	if(flag != 0)
	{
		perror("pthread_rwlock_init");
		exit(EXIT_FAILURE);
	}

	pthread_t pid_w1;
	pthread_create(&pid_w1, NULL, writer, NULL);	
	pthread_t pid_w2;
	pthread_create(&pid_w2, NULL, writer, NULL);	
	pthread_t pid_w3;
	pthread_create(&pid_w3, NULL, writer, NULL);	
	
	
	pthread_t pid_r1;
	pthread_create(&pid_r1, NULL, reader, NULL);	
	pthread_t pid_r2;
	pthread_create(&pid_r2, NULL, reader, NULL);	
	pthread_t pid_r3;
	pthread_create(&pid_r3, NULL, reader, NULL);	

	
	

	pthread_join(pid_w1, NULL);
	pthread_join(pid_w2, NULL);
	pthread_join(pid_w3, NULL);
	pthread_join(pid_r1, NULL);
	pthread_join(pid_r2, NULL);
	pthread_join(pid_r3, NULL);
	pthread_rwlock_destroy(&rwlock);
}
