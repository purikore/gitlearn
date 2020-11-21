
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int data = 0;;
void * func(void * arg)
{
	//pthread_detach(pthread_self());
	//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	int i;
	int *p = (int *)malloc(4);
	*p = 28;
	for(i=0;i<10;i++)
	{
		data ++;
		printf("func thread data = %d\n",data);
		sleep(1);
		if(i == 4)
			//pthread_exit((void *)p);
			return (void *)p;
	}
}


int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,func,NULL);
	//pthread_detach(tid);//这样设置会有一个问题，就是设置之前新线程可能已经结束了
	//所以一般由线程自己来设置这个分离属性
	sleep(3);
	
	//pthread_cancel(tid);
	int *q;
	pthread_join(tid,(void **)&q);
	printf("%d\n",*q);
	free(q);
	
}

