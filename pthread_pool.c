#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include "pthread_pool.h"
extern Pool * pool;

void pthread_pool_init(int max_size)
{
	pool = (Pool *)malloc(sizeof(Pool));
	pthread_mutex_init(&(pool -> pmt), NULL);
	pthread_cond_init(&(pool -> pct), NULL);
	
	pool -> pids = (pthread_t *)malloc(sizeof(pthread_t) * max_size);
	pool -> queue = create_queue();
	
	pool -> max_pool_size = max_size;
	pool -> shutdown = FALSE;
	int * num = (int *)malloc(sizeof(int) * max_size);
	for(int i = 0; i < max_size; i++)
	{
		*(num + i) = i;
		pthread_create(pool -> pids + i, NULL, pthread_pool_running, (void *)(num + i));
	}
}

void * pthread_pool_running(void * argv)
{
	int * no = (int *)argv;
	printf("线程0x%lx编号%d开始运行\n", pthread_self(), *no);
	while(1)
	{
		pthread_mutex_lock(&(pool -> pmt));
		/*如果已经开始销毁,那么就不再进行等待*/
		/*为啥不用if,防止signal全部唤醒的bug*/
		while(pool -> queue -> wait_task_size == 0 && !(pool -> shutdown))
		{	
			printf("线程0x%lx编号%d正在等待\n", pthread_self(), *no);
			pthread_cond_wait(&(pool -> pct), &(pool -> pmt));
		}
		/*必须队列中全部执行完并且shutdown才能关闭线程*/
		if(pool -> queue -> wait_task_size == 0 && pool -> shutdown)
		{
			pthread_mutex_unlock(&(pool -> pmt));
			printf("线程0x%lx编号%d结束运行\n", pthread_self(), *no);
			//free(no);
			pthread_exit(NULL);
		}
		/*assert是用于调试*/
		assert(pool -> queue -> wait_task_size != 0);
		
		Task * temp = pool -> queue -> first;
		pool -> queue -> first = pool -> queue -> first -> next;
		pool -> queue -> wait_task_size--;
		pthread_mutex_unlock(&(pool -> pmt));
		temp -> next = NULL;
		printf("线程0x%lx编号%d开始执行任务\n", pthread_self(), *no);
		//(*(temp -> process))(temp -> argv);
		temp -> process(temp -> argv);
		printf("线程0x%lx编号%d结束任务\n", pthread_self(), *no);
		free(temp);
	}
}

void pthread_pool_destroy()
{
	pool -> shutdown = TRUE;
	pthread_cond_broadcast(&(pool -> pct));
	for(int i = 0; i < pool -> max_pool_size; i++)
	{
		pthread_join(*(pool -> pids + i), NULL);
	}
	pthread_mutex_destroy(&(pool -> pmt));
	pthread_cond_destroy(&(pool -> pct));
	free(pool -> pids);
	free(pool -> queue);
	free(pool);
}
