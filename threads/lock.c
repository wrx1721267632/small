/*************************************************************************
	> File Name: lock.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月28日 星期二 20时44分31秒
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>

static pthread_mutex_t testlock;

void* run(void)
{
    pthread_mutex_lock(&testlock);
    printf("run run!\n");
    pthread_mutex_unlock(&testlock);
}

int main()
{
    pthread_t thid;

    pthread_mutex_init(&testlock,NULL);
    pthread_mutex_lock(&testlock);
    printf("main run!\n");
    pthread_create(&thid, NULL,(void *) run, NULL);
    sleep(1);
    printf("main run !\n");
    pthread_mutex_unlock(&testlock);
    sleep(1);
    pthread_join(thid, NULL);
    pthread_mutex_destroy(&testlock);
    return 0;
}
