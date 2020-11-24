#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "pthread_pool.h"
Pool * pool = NULL;
void * func(void * argv)
{
	sleep(2);
	printf("输出第%d个数据\n", *(int *)argv);
	sleep(2);
}
int main()
{
	pthread_pool_init(10);
	int * num = (int *)malloc(sizeof(int) * 20);
	for(int i = 0; i < 20; i++)
	{
		*(num + i) = i;
		enqueue(pool -> queue, func, num + i);
	}
	pthread_pool_destroy();
	free(num);
	return 0;
}
