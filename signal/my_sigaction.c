/*************************************************************************
	> File Name: my_sigaction.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月15日 星期六 09时33分53秒
 ************************************************************************/

#include<stdio.h>
#include <signal.h>
#include <unistd.h>

int temp = 0;

//信号处理函数
void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
    sleep(5);
    temp++;
    printf("temp: %d, signo: %d\n",temp, signo);
    printf("after sleep!\n");
}

int main()
{
    struct sigaction act;

    //对act进行复制
    act.sa_handler = handler_sigint;
    act.sa_flags =  SA_NOMASK;

    //安装信号处理函数
    sigaction(SIGINT, &act, NULL);

    while(1)
        ;

    return 0;
}
