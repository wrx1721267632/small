/*************************************************************************
    > File Name: getchar.c
    > Author: xinxin
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月24日 星期五 15时29分46秒
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
	char *buf = NULL;
	int len = 0;
	int ch;

	buf = (char *)malloc(256);
	if (buf == NULL) {
		perror("malloc failed");
		exit(-1);
	}
	memset(buf, 0, 256);

	ch = getchar();
	while(len < 256 && ch != '\n')
	{
		buf[len++] = ch;
		ch = getchar();
	}
	if (len == 256) {
		printf("too long!\n");
		exit(-1);
	}

//	buf[len] = '\n';
//	len ++;
//	buf[len] = '\0';
    printf("%d\n",strlen(buf));
	puts(buf);
	return 0;
}
