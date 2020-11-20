#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_rwlock_t rwlock;
int data = 0;
void * reader(void * argv)
{
	while(1)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf("子进程读到%d\n", data);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}

void * writer(void * argv)
{
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		data++;
		printf("父进程写到%d\n", data);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}
int main()
{
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
