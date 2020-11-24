#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "pthread_pool.h"

Pool * pool = NULL;

void pthread_pool_init(int max_size)
{
	pool = (Pool *)malloc(sizeof(Pool));
	pthread_mutex_init(&(pool -> pmt), NULL);
	pthread_cond_init(&(pool -> pct), NULL);
	
	pool -> pids = (pthread_t *)malloc(sizeof(pthread_t) * max_size);
	pool -> queue_head = NULL;
	
	pool -> max_pool_size = max_size;
	pool -> wait_task_size = 0;
	pool -> shutdown = FALSE;
	for(int i = 0; i < max_size; i++)
	{
		pthread_create(pool -> pid + i, NULL, pthread_pool_running, (void *)i);
	}
}

void * pthread_pool_running(void * argv)
{
	int * no = (int *)argv;
	printf("线程0x%x编号%d开始运行\n", pthread_self(), *no);
	while(1)
	{
		pthread_mutex_lock(&(pool -> pmt));
		if()
		
	}
}
