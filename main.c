#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "pthread_pool.h"
#include "mycp.h"
Pool * pool = NULL;
int main()
{
	Dcp * dcp = (Dcp *)malloc(sizeof(Dcp));
	strcpy(dcp -> src, "/mnt/d/linux_share/第二阶段/day38线程/mycp.c");
	strcpy(dcp -> dest, "test");
	pthread_pool_init(10);
	
	enqueue(pool -> queue, pthread_cp, (void *)dcp);
	pthread_pool_add(5);
	pthread_pool_destroy();
	free(dcp);
	return 0;
}
