/*************************************************************************
	> File Name: oncerun.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月27日 星期一 21时59分55秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;
void run (void)
{
    printf("run id is %lu\n",pthread_self());

}

void *thread1(void *arg)
{
    printf("thread1 id is %lu\n",pthread_self());
    pthread_once(&once, run);
    printf("thread1 ends\n");
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

}

void *thread2(void *arg)
{
    printf("thread2 id is %lu\n",pthread_self());
    pthread_once(&once, run);
    printf("thread2 ends\n");
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
}

int main(void)
{
    pthread_t thid1, thid2;
    pthread_create(&thid1, NULL, thread1, NULL);
    pthread_create(&thid2, NULL, thread2, NULL);
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    printf("3\n");
    sleep(3);
    printf("main ends!\n");
    exit(0);
}
