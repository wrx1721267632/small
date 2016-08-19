/*************************************************************************
	> File Name: file.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月28日 星期二 11时01分15秒
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void run(void)
{
    int fd ;
    fd = open ("file", O_RDWR|O_CREAT|O_TRUNC, 0766);
    printf("thread is %d\n",fd);
    printf("thread id is %lu\n",pthread_self());
}

int main()
{
    pthread_t thid;
    int fd;
    fd = open("file",O_RDWR|O_CREAT|O_TRUNC, 0766);
    printf("main  is  %d\n",fd);
    printf("main id is %lu\n", pthread_self());
    pthread_create(&thid, NULL, (void*) run , NULL);
    sleep(3);
    pthread_exit(0);
}
