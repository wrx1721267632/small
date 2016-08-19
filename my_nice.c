/*************************************************************************
    > File Name: my_nice.c
    > Author: xinxin
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月23日 星期四 22时13分25秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>

int main()
{
	pid_t pid;
	int stat_val = 0;
	int oldpri, newpri;

	pid = fork();
	switch(pid) {
		case 0:
			printf("child process is runing,curpid = %d,parentpid = %d\n", pid, getppid());
			oldpri = getpriority(PRIO_PROCESS,getpid());

			printf("oldpri = %d\n",oldpri);
			newpri=nice(2);
			printf("newpri = %d\n",newpri);
			exit(0);
		case -1:
			printf("error\n");
			break;
		default:
			printf("parent procsee is running,childpid = %d,parentpid = %d\n", pid, getpid());
			break;
	}
	wait(&stat_val);
	exit(0);
}
