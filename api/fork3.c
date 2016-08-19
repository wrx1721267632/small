/*************************************************************************
    > File Name: fork3.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月21日 星期二 16时46分42秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	pid_t pid;

	pid = fork();
	switch(pid){
		case 0:
			printf("child process running, childpid:%d, parentpid:%d\n", getpid(), getppid());
			sleep(5);
			printf("child process running, childpid:%d, parentpid:%d\n", getpid(), getppid());
			printf("child process exit!\n");
			break;
		case -1:
			printf("error!");
            break;
		default:
			printf("parent process running, pid = %d\n", getpid());
			sleep(1);
			printf("parent process exit!\n");
		    break;
	}
	return 0;
}
