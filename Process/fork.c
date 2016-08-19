/*************************************************************************
    > File Name: fork.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月21日 星期二 15时39分23秒
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
			printf("child process running,pid = %d,,getpid = %d,parentpid = %d\n", pid,  getpid(), getppid());
			break;
		case -1:
			printf("error");
		default :
			printf("parent process running,childpid = %d,parentpid = %d\n", pid, getpid());
			break;
	}
	return 0;
}
