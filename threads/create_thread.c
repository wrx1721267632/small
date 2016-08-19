/*************************************************************************
	> File Name: create_thread.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月27日 星期一 21时28分06秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int *thread(void *arg)
{
    printf("this is a new thread ID %lu\n",pthread_self());
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    printf("2\n");
    return NULL;
}

int main(void)
{
    pthread_t thid;

    printf("main thread ,ID is %lu\n",pthread_self());
    if(pthread_create(&thid, NULL, (void *)thread, NULL) != 0) {
        printf("thread create error !\n");
        exit(1);
    }
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    printf("1\n");
    sleep(3);
    exit(0);
}
