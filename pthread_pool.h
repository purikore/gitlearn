#ifndef __PTHREAD_POOL_H__
#define __PTHREAD_POOL_H__

#define boolean unsigned char
#define TRUE 1
#define FALSE 0
/*
	任务队列
*/
typedef struct pthread_pool
{
	pthread_mutex_t pmt;
	pthread_cond_t pct;
	
	pthread_t * pids;
	struct task_queue * queue_head;
	
	int max_pool_size;
	int wait_task_size;
	boolean shutdown;
}Pool;

typedef struct task_queue
{
	void *(*task) (void * argv);
	void * argv;
	struct task_queue * next;
}Queue;


#endif
