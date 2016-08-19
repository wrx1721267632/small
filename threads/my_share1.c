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
#include<sys/types.h>
#include<string.h>

typedef struct node{
    int num;
    struct node *next;
    struct node *self;
}* NODE;

int main()
{
    const int SHM_SIZE = 1000000;
    const char *name = "/my_shm";

    int shm_fd;
    void* ptr;

    NODE p1 = NULL;
    NODE p2 = NULL;

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
    p1 = (NODE)malloc(sizeof(struct node));
    p2 = (NODE)malloc(sizeof(struct node));
    
    for (int i=0; i<25;i++)
    //while (1)
    {
        lseek(shm_fd, 0, SEEK_SET);
        read(shm_fd,p1,sizeof(struct node));

        int sum = 0;
        while(1)
        {
            sum++;
            read(shm_fd,p2,sizeof(struct node));
            if (p1->next != p2->self)
            {
                break;
            }
            memcpy(p1,p2,sizeof(struct node));
        }
        printf("the count of node is: %d\n", sum);
        usleep(400000);
    }

    return 0;
}
