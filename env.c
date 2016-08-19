/*************************************************************************
    > File Name: env.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月22日 星期三 10时58分49秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>

//extern char **environ;

int main(int argc,char **argv,char **envp)
{
	int i;
	printf("Arguvment:\n");
	for (i = 0; i < argc; i++ ) {
		printf("argv[%d] is %s\n", i, argv[i]);
	}
	printf("Environment:\n");
	for (i = 0; envp[i] != NULL; i++) {
		printf("%s\n", envp[i]);
	}
	return 0;
}
