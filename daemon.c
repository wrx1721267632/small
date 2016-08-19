/*************************************************************************
    > File Name: daemon.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月22日 星期三 09时22分00秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <sys/param.h>


int init_daemon()
{
	int pid;
	int i;
	
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGHUP,SIG_IGN);

	pid=fork();
	if (pid > 0) {
		exit(0);
	} else if(pid == -1) {
		printf("error");
		return -1;
	}
	setsid();
	
	pid = fork();
	if (pid > 0) {
		exit(0);
	} else if(pid == -1) {
		printf("error");
		return -1;
	}

	for (i = 0; i < NOFILE; close(i++));

	chdir("/");

	umask(0);

	signal(SIGCHLD,SIG_IGN);

	return 0;
}

int main()
{
	time_t now;
	init_daemon();

	syslog(LOG_USER|LOG_INFO,"测试守护进程!\n");
	while(1){
		sleep(8);
		time(&now);
		syslog(LOG_USER|LOG_INFO,"系统时间： \t%s\t\t\n", ctime(&now));
	}
}
