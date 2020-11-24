#ifndef __PTHREAD_POOL_H__
#define __PTHREAD_POOL_H__
#include "queue.h"
#define boolean unsigned char
#define TRUE 1
#define FALSE 0
/*  线程池 */
typedef struct pthread_pool
{
	pthread_mutex_t pmt;
	pthread_cond_t pct;
	
	pthread_t * pids;
	Queue * queue;
	
	int max_pool_size;
	boolean shutdown;
}Pool;

void pthread_pool_init(int);
void * pthread_pool_running(void *);
void pthread_pool_destroy();

#endif
