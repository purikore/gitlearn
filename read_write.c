#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
pthread_rwlock_t rwlock;

void * readr(void * argv)
{
	
}

void * writer(void * argv)
{
	
}
int main()
{
	int flag = pthread_rwlock_init(&rwlock, NULL);
	if(flag != 0)
	{
		perror("pthread_rwlock_init");
		exit(EXIT_FAILURE);
	}
	

	
	pthread_rwlock_destroy(&rwlock);
}
