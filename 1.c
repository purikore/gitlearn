#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
pthread_mutex_t pmt;
void * func(void *argv)
{
	int * a = (int *)argv;
	for(int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&pmt);
		(*a)++;
		pthread_mutex_unlock(&pmt);
	}
	pthread_exit(NULL);
}
int main()
{
	pthread_mutex_t pmt;
	int flag = pthread_mutex_init(&pmt, NULL);
	if(flag == -1)
	{
		perror("pthread_mutex_init");
		exit(EXIT_FAILURE);
	}
	int *a = (int *)malloc(sizeof(int));
	*a = 0;
	pthread_t pid;
	pthread_create(&pid, NULL, func, (void *)a);
	pthread_t pid1;
	pthread_create(&pid1, NULL, func, (void *)a);
	
	pthread_join(pid, NULL);
	pthread_join(pid1, NULL);
	printf("%d\n",*a);
	pthread_mutex_destroy(&pmt);
	return 0;
}
