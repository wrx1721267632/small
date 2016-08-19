/*************************************************************************
    > File Name: opendir.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月20日 星期一 09时30分53秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *ptr;
	
	if ((dir = opendir(argv[1])) == NULL) {
		perror ("open");
		exit(1);
	}
	while ((ptr = readdir(dir)) != NULL) {
		printf("filename: %s\n",ptr->d_name);
	}
	closedir(dir);
	return 0;
}
