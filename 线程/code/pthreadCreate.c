#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int data = 0;

void * func(void * arg)
{
	int i;
	printf("%lf\n",*(double*)arg);
	for(i=0;i<100000;i++)
	{
		data ++;
	}
	pthread_exit(NULL);
	printf("func thread data = %d\n",data);
}

int main()
{
	int i=0;
	double d = 3.14;
	pthread_t tid;
	pthread_create(&tid,NULL,func,(void *)&d);
	
	for(i=0;i<100000;i++)
	{
		data ++;
	}
	printf("main thread data = %d\n",data);

	//return 0;
	while(1);
}



