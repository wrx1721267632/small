/*************************************************************************
	> File Name: tsd.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月28日 星期二 17时01分25秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <pthread.h>

pthread_key_t key;

void *thread2(void)
{
    int tsd = 5;

    printf("thread %lu is running \n",pthread_self());
    pthread_setspecific(key, (void *) tsd );
    printf("thread %lu returns %d \n",pthread_self(),pthread_getspecific(key));
}

void *thread1(void)
{
    int tsd = 0;
    int a = 3;
    pthread_t thid2;

    printf("thread %lu is running\n",pthread_self());
    pthread_setspecific (key, (void *)tsd);
    pthread_setspecific (key, (void *)a);
    pthread_create(&thid2, NULL, (void *) thread2, NULL);
    sleep(2);
    printf("thread %lu returns %d\n",pthread_self(), pthread_getspecific(key));
}

int main()
{
    pthread_t thid1;

    printf("man thread is run!\n");
    pthread_key_create(&key, NULL);
    pthread_create(&thid1, NULL, (void *)thread1,NULL);
    sleep(3);
    pthread_key_delete(key);
    printf("main thread exit!\n");
    return 0;
}
