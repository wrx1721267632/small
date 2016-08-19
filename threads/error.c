/*************************************************************************
	> File Name: error.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月29日 星期三 11时26分43秒
 ************************************************************************/

#include<stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    printf("error:%s\n", strerror(2));
    return 0;
}
