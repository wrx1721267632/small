/*************************************************************************
	> File Name: thread.c
	> Author: 
	> Mail: 
	> Created Time: 2016年08月15日 星期一 20时23分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<pthread.h>
#include<sys/mman.h>

typedef struct node{
    int num;
    struct node *next;
    struct node *self;
}* NODE;

NODE phead = NULL;

int main()
{
    const int SHM_SIZE = 1000000;
    const char *name = "/my_shm";

    int shm_fd;
    void *ptr;
    
    NODE p, tail, prev;

    shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("In my_open()");
        exit(1);
    }

    ftruncate(shm_fd, SHM_SIZE);

    ptr = mmap(0, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("MAP failed\n");
        return -1;
    }
    
    for(int i=0; i<20; i++)
   // while(1)
    {
        p = (NODE)malloc(sizeof(struct node));
        int x = rand()%100;
        printf("insert the node is: %d\n",x);
        p->num = x;
        p->next = NULL;
        p->self = p;
        if (phead == NULL) {
            phead = p;
            tail = phead;
        } else {
            tail->next = p;
            prev = tail;
            tail = p;
            write(shm_fd,prev,sizeof(struct node));
        }
        usleep(500000);
    }
    
    if (shm_unlink(name) == -1) {
        perror("in shm_unlink()");
        exit(1);
    }
    return 0;
}
