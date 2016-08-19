/*************************************************************************
    > File Name: fork2.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月21日 星期二 15时49分41秒
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
	char *msg;
	int k = 0;

	pid = fork();
	switch(pid){
		case 0:
			k = 3;
			msg = "child process running";
			break;
		case -1:
			printf("error!");
			break;
		default:
			k = 5;
			msg = "parent process runing";
			break;
	}

	while(k > 0){
		printf("%s\n", msg);
		printf("1\n");
		k--;
	}
	exit(0);
}
