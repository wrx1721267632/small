/*************************************************************************
	> File Name: join.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月28日 星期二 14时33分33秒
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>

void run(void)
{
    printf("thread id is %lu\n",pthread_self());
    sleep(3);
    printf("thread is ends!\n");
    pthread_exit(0);
}

int main()
{
    pthread_t thid;
    int status;
    printf("main id is %lu\n",pthread_self());
    pthread_create(&thid, NULL ,(void *) run , NULL);
    pthread_join(thid,(void*) &status );
    printf("status is %d\n",status);
    printf("main is ends!\n");
    return 0;
}
