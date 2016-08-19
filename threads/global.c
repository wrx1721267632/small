/*************************************************************************
	> File Name: global.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月03日 星期一 09时47分38秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t           mutex;
int globalnumber = 0;

void write_globalnumber()
{
    printf("write_globalnumber running\n");
    pthread_mutex_lock(&mutex);
    globalnumber++;
    printf("write_globalnumber : %d\n",globalnumber);
    globalnumber++;
    printf("write_globalnumber : %d\n",globalnumber);
    globalnumber++;
    printf("write_globalnumber : %d\n",globalnumber);
    globalnumber++;
    printf("write_globalnumber : %d\n",globalnumber);
    pthread_mutex_unlock(&mutex);
}

void read_globalnumber() 
{
    int temp;
    printf("read_globalnumber running\n");
    pthread_mutex_lock(&mutex);
    temp = globalnumber;
    pthread_mutex_unlock(&mutex);
    printf("read_globalnumber : %d\n",globalnumber);
    return (temp);
}

int main()
{
    pthread_t thid1;
    pthread_t thid2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thid1, NULL, (void*)write_globalnumber, NULL);
    pthread_create(&thid2, NULL, (void*)read_globalnumber, NULL);
    printf("main running\n");
    sleep(4);
    return 0;
}
