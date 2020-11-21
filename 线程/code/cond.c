

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
pthread_mutex_t mutex;//定义一个线程互斥锁
pthread_cond_t cond;//定义一个线程条件变量
int data = 0;

/*
void * func(void * arg)
{
	while(1)
	{
		if(data >= 10000000)
		{
			printf("data = %d\n",data);
			pthread_mutex_lock(&mutex);
			data = 0;
			pthread_mutex_unlock(&mutex);
			printf("消费数据\n");
		}
	}
	
}

int main()
{
	int i=0;
	pthread_mutex_init(&mutex,NULL);//初始化线程互斥锁
	pthread_t tid;
	pthread_create(&tid,NULL,func,NULL);
	
	//主线程生成数据
	while(1)//一直生产数据
	{
		pthread_mutex_lock(&mutex);
		data++;

		pthread_mutex_unlock(&mutex);
	}
	
	pthread_join(tid,NULL);

	pthread_mutex_destroy(&mutex);
	return 0;
}

*/


void * func(void * arg)
{
	while(1)//这个循环和前面轮询的循环有区别吗？？
	//代表消费者在重复的消费数据，轮询的那个while代表“轮询”
	{
		pthread_mutex_lock(&mutex);

		pthread_cond_wait(&cond,&mutex);
		if(data >= 10000000)//还是需要判断条件是否成立
				//因为，可能已经被别人消费了
		{
			printf("data = %d\n",data);
			data = 0;
			printf("消费数据\n");
			pthread_mutex_unlock(&mutex);
		}
			
	}
	
}

int main()
{
	int i=0;
	pthread_mutex_init(&mutex,NULL);//初始化线程互斥锁
	pthread_cond_init(&cond,NULL);//初始化条件变量
	pthread_t tid;
	pthread_create(&tid,NULL,func,NULL);
	
	//主线程生成数据
	while(1)//一直生产数据
	{
		pthread_mutex_lock(&mutex);
		data++;
		if(data == 10000000)//条件成立
		{
			//唤醒等待的线程
			pthread_cond_signal(&cond);
		}
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_join(tid,NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}

