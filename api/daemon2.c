/*************************************************************************
    > File Name: daemon2.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月22日 星期三 10时06分12秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int i, fd;
	char *buf = "this is a daemon program.\n";
	if((pid = fork()) == -1){
		printf("error");
		exit(1);
	} else if (pid > 0) {
		exit(0);
	}
	
	setsid();
	chdir("/");
	umask(0);
	for(i = 0; i < getdtablesize(); close(i++));
	while(1) {
		if((fd = open("/tmp/daemon.log", O_CREAT|O_WRONLY|O_APPEND,0600))<0)
		{
			printf("error");
			exit(1);
		}
		write(fd, buf, strlen(buf)+1);
		close(fd);
		sleep(10);
		printf("Never output!\n");
	}
	return 0;
}
