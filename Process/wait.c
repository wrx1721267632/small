/*************************************************************************
    > File Name: wait.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月22日 星期三 15时06分06秒
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
	char *msg;
	int k;
	int exit_code;

	printf("Study how to get exit code!\n");
	pid = fork();
	switch(pid){
		case -1:
			perror("error\n");
		case 0:
			exit_code = 37;
			k = 5;
			msg = "child process is running";
			break;
		default:
			exit_code = 0;
			break;
	}

	if (pid != 0) {
		int stat_val;
		pid_t child_pid;
		child_pid = wait(&stat_val);
printf("%d\n",stat_val);
	    printf("child process has exixed, pid = %d,parentpid = %d\n",child_pid, getpid());
		if (WIFEXITED(stat_val)) {
			printf("child exited with code %d\n",WEXITSTATUS(stat_val));
		} else {
			printf("child exited error!\n");
		}
	} else {
		while (k-- > 0) {
			puts(msg);
			sleep(1);
		}
	}
	exit(exit_code);
}
