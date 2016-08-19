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

	pid = vfork();
	switch(pid) {
		case 0:
			printf("child process is runing,curpid = %d,parentpid = %d\n", pid, getppid()); 
            printf("0 : %d",getpriority(PRIO_PROCESS,0));
			oldpri = getpriority(PRIO_PROCESS,getpid());

			printf("oldpri = %d\n",oldpri);
			newpri=nice(2);
			printf("newpri = %d\n",newpri);
            printf("0 : %d\n",getpriority(PRIO_PROCESS,0));
            printf("pid_ : %d\n",getpriority(PRIO_PROCESS,getpid()));
			exit(0);
		case -1:
			printf("error\n");
			break;
		default:
			printf("parent procsee is running,childpid = %d,parentpid = %d\n", pid, getpid());
            printf("0 : %d\n",getpriority(PRIO_PROCESS,0));
            printf("pid_t : %d\n",getpriority(PRIO_PROCESS,getpid()));
			break;
	}
	wait(&stat_val);
	exit(0);
}
