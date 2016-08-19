/*************************************************************************
    > File Name: studyuid.c
    > Author: xinxin
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月23日 星期四 20时02分49秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

extern int errno;

int main()
{
	int fd;

	printf("uid study: \n");
	printf("process's uid = %d, euid = %d\n",getuid(), geteuid());

	if((fd = open("test.c",O_RDWR)) == -1) {
		printf("open failure, errno is %d : %s\n",errno, strerror(errno));
		exit(1);
	}
	else{
		printf("open sucessfully!\n");
	}
	close(fd);
	exit(0);
}
