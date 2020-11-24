#ifndef __QUEUE_H__
#define __QUEUE_H__


typedef struct task
{
        void *(*process) (void * argv);
        void * argv;
        struct task * next;
}Task;

typedef struct queue
{
        Task * first;
        Task * last;
        int wait_task_size;
}Queue;

Queue * create_queue();
void enqueue(Queue *, void * (*process) (void * argv), void *);
#endif
