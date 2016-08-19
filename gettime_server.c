/*************************************************************************
	> File Name: gettime_server.c
	> Author: 
	> Mail: 
	> Created Time: 2015年11月16日 星期一 22时42分05秒
 ************************************************************************/

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
#define LISTENQ 12

void err_quit(const char *err_string, int line)
{
    fprintf(stderr, "line:%d ", line);
    perror(err_string);
    exit(1);
}

int Socket(int family, int type, int protocol)
{
    int n;
    if( (n = socket(family, type, protocol)) < 0 )
        err_quit("socker error", __LINE__);
    return (n);
}

int main(int argc, char ** argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(4507);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) 
        err_quit("bind error", __LINE__);

    if (listen(listenfd, LISTENQ) <  0)
        err_quit("listen error", __LINE__);

    while (1) {
        if((connfd = accept(listenfd, (struct sockaddr*) NULL, NULL)) < 0)
            err_quit("acceot error", __LINE__);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if (write(connfd, buff, strlen(buff)) < 0)
            err_quit("write error", __LINE__);
        if ( close(connfd) < 0)
            err_quit("close error", __LINE__);
    }
    exit(0);
}
