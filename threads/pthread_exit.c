/*************************************************************************
	> File Name: pthread_exit.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月28日 星期二 10时24分48秒
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
void run(void *arg)
{
    printf("pthread id is %lu\n",pthread_self());
    sleep(1);
    printf("pthread is ends\n");
}

int main()
{
    pthread_t thid;
    printf("main id is %lu\n",pthread_self());
    pthread_create(&thid, NULL,(void*) run, NULL);
    printf("main is ends\n");
    pthread_exit(0);
    //return 0;
}
