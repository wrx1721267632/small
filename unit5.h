/*************************************************************************
	> File Name: unit5.h
	> Author: 
	> Mail: 
	> Created Time: 2016年03月11日 星期五 13时37分56秒
 ************************************************************************/

#ifndef _UNIT5_H
#define _UNIT5_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

#define MAXLINE 100

void str_echo(int sockfd)
{
    size_t n;
    char buf[MAXLINE];
    
again:
    while ( (n = read(sockfd, buf, MAXLINE)) > 0) 
    {
        write(sockfd, buf, n);
    }

    if (n < 0 && errno == EINTR)
    {
        goto again;
    }
    else if (n < 0)
    {
        printf("str_echo: read error");
    }
}

void str_cli(FILE * fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while (fgets(sendline, MAXLINE, FP) != NULL)
    {
        write(sockfd, sendline, strlen(sendline));
        if (readline(sockfd, recvline, MAXLINE) == 0)
        {
            printf("str_cli: server terminated prematurely!");
        }
        fputs(recvline, stdout);
    }
}

void sig_wait(int signo)
{
    pid_t pid;
    int stat;

    pid = wait(&stat);
    printf("child %d terminated\n", pid);
    return;
}

void sig_waitpid(int signo)
{
    pid_t pid;
    int stat;
    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printf("child %d terminated\n", pid);
    }
    return;
}

void str_cli2(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while (fgets(sendline, MAXLINE, fp) != NULL)
    {
        write(sockfd, sendline, 1);
        sleep(1);
        write(sockfd,sendline + 1, strlen(sendline) - 1);
        if (readline(sockfd, recvline, MAXLINE) == 0)
        {
            printf("strcli: server terminated prematurely");
        }
        fputs(recvline, stdout);
    }
}
#endif
