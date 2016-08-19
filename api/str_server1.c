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

void str_echo(int sockfd)
{
    long arg1, arg2;
    ssize_t n;
    char line[MAXLINE];

    while (1) 
    {
        if ( (n = read(sockfd, line, MAXLINE)) == 0)
        {
            return ;
        }
        if (n == -1) continue;
        
        if (sscanf(line, "%ld%ld", &arg1, &arg2) == 2) 
        {
            snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
        }
        else 
        {
            snprintf(line, sizeof(line), "input error!\n");
        }

        n = strlen(line);
        write(sockfd, line, n);
    }
}

int main()
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t client;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = 5375;

    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    for (;;) 
    {
        client = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &client);
        if ( (childpid = fork()) == 0 )
        {
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }
}
