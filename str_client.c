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

void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1;
    fd_set rset;
    char sendline[MAXLINE], recvline[MAXLINE];

    FD_ZERO(&rset);
    while(1) 
    {
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = ((fileno(fp) > sockfd) ? fileno(fp) : sockfd) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)) 
        {
            if (read(sockfd, recvline, MAXLINE) == 0)
            { 
                printf("str_cli: recvline terminated prematurely\n");
                exit(0);
            }
            fputs(recvline, stdout);
        }

        if (FD_ISSET(fileno(fp), &rset))
        {
            if (fgets(sendline, MAXLINE, fp) == NULL)
            {
                return ;
            }
            write(sockfd, sendline, MAXLINE);
        }
        bzero(recvline, MAXLINE);
        bzero(sendline, MAXLINE);
    }
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) 
    {
        printf("usage: tcpcli <IPaddress>");
        return 0;
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = 5375;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);

    exit(0);
}
