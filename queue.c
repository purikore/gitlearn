#include <stdlib.h>
#include <pthread.h>
#include "pthread_pool.h"
extern Pool * pool;
Queue * create_queue()
{
        Queue * queue = (Queue *)malloc(sizeof(Queue));
        queue -> first = NULL;
        queue -> last = NULL;
        queue -> wait_task_size = 0;
        return queue;
}

void enqueue(Queue * queue, void * (*process) (void * argv), void * argv)
{
	Task * task = (Task *)malloc(sizeof(Task *));
	task -> process = process;
	task -> argv = argv;
	task -> next = NULL;
	pthread_mutex_lock(&(pool -> pmt));
	if(queue -> wait_task_size == 0)
	{
		queue -> first = task;
		queue -> last = task;
		queue -> wait_task_size++;
	} else {
		queue -> last -> next = task;
		queue -> last = task;
		queue -> wait_task_size++;
	}
	pthread_mutex_unlock(&(pool -> pmt));
	pthread_cond_signal(&(pool -> pct));
}
