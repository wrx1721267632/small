/*************************************************************************
    > File Name: diffork.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月21日 星期二 19时48分13秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int globvar = 5;

int main()
{
	pid_t pid;
	int i, var = 1;

	printf("fork is diffirent vfork\n");

   	pid = fork();
//	pid = vfork();
	switch(pid){
		case 0:
			i = 3;
			while(i-- > 0){
				printf("child process is running!\n");
				var ++;
				globvar ++;
				sleep(1);
			}
			printf("child's var = %d, globvar = %d\n", var, globvar);
			exit(0);
		case -1:
			printf("error!");
			exit(0);
		default:
			i = 5;
			while(i-- > 0){
				printf("parent process is running!\n");
				var ++;
				globvar ++;
				sleep(1);
			}
		    printf("parent's var = %d,globvar = %d\n ", var, globvar);
		    exit(0);
	}
}
