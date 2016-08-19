/*************************************************************************
    > File Name: execve.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月22日 星期三 11时42分57秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,char **argv, char **environ)
{
	pid_t pid;
	int stat_val;
	printf("Exec example!\n");
	pid = fork();
	switch(pid) {
		case -1:
			printf("error!\n");
			break;
		case 0:
			printf("child process is running!\n");
			printf("My pid = %d, parentpid = %d\n", getpid(), getppid());
			printf("uid = %d, gid = %d\n", getuid(), getgid());
			execve("processimage", argv, environ);
			printf("process never go here!");
			exit(0);
		default:
			printf("parent process is running!\n");
			break;
	}
	wait(&stat_val);
	printf("%d\n",stat_val);
	return 0;
}
