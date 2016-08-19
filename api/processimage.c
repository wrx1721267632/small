/*************************************************************************
    > File Name: processimage.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月22日 星期三 11时36分58秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(int argc,char **argv,char **environ)
{
	int i;
	printf("i am a process image!\n");
	printf("My pid = %d, parentpid = %d\n", getpid(), getppid());
	printf("uid = %d, gid = %d\n",getuid(),getgid());
	for (i = 0; i < argc; i++) {
		printf("argv[%d]:%s\n", i, argv[i]);
	}
}
