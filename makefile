.PHONY:clean
CC:=gcc
main:main.c queue.c pthread_pool.c
	$(CC) -g $^ -o $@ -pthread
