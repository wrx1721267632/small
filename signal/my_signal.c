/*************************************************************************
	> File Name: my_signal.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月14日 星期五 09时53分23秒
 ************************************************************************/

#include<stdio.h>
#include <signal.h>

void handler_sigint(int signo)
{
    printf("recv SIGINT!\n");
    printf("%d\n",signo);
}

int main()
{
    signal(SIGINT, handler_sigint);
    while(1){}

    return 0;
}
