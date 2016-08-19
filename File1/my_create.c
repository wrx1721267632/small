/*************************************************************************
    > File Name: my_create.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月20日 星期一 08时46分32秒
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
	int fd;
	char *buf;
	if ((fd = creat("123.txt",S_IRWXU|S_IRWXG|S_IRWXO)) < 0) {
		perror("open");
		exit(1);
	}
	if (read(fd, buf, 10) < 0) {
		printf("read\n");
		exit(1);
	}
    return 0;
}
