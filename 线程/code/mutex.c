#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
pthread_mutex_t mutex;//定义一个线程互斥锁
int data = 0;

void * func(void * arg)
{
	int i;
	
	for(i=0;i<10000000;i++)
	{
		//p操作
		pthread_mutex_lock(&mutex);
		data ++;
		//V操作
		pthread_mutex_unlock(&mutex);
	}
	//pthread_exit(NULL);
	
}

int main()
{
	int i=0;
	pthread_mutex_init(&mutex,NULL);//初始化线程互斥锁
	pthread_t tid;
	pthread_create(&tid,NULL,func,NULL);
	
	for(i=0;i<10000000;i++)
	{
		//p操作
		pthread_mutex_lock(&mutex);
		data ++;
		//V操作
		pthread_mutex_unlock(&mutex);
	}
	
	//return 0;
	pthread_join(tid,NULL);
	printf("main thread data = %d\n",data);

	pthread_mutex_destroy(&mutex);
	return 0;
}



