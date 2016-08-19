/*************************************************************************
	> File Name: gettime_client.c
	> Author: 
	> Mail: 
	> Created Time: 2015年11月16日 星期一 22时05分05秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/errno.h>

#define MAXLINE 100

void err_quit(const char *err_string, int sum)
{
    perror(err_string);
    printf("%d\n",sum);
    exit(1);
}

int main(int argc, char** argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    errno=0;
    int sum = 0;

    if (argc != 2) 
        err_quit("usage: a.out <Ipaddress>", sum);

while(sum != 20){    
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        err_quit("socket error", sum);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(4507);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        sprintf("inet_pton error for %s", argv[1],recvline);
        err_quit(recvline, sum);
    }
    
    if (connect(sockfd,(struct sockaddr*)  &servaddr, sizeof(servaddr)) < 0)
        err_quit("connect error", sum);
    while( (n = read(sockfd, recvline, MAXLINE)) > 0 ) {
        recvline[n] = 0;
        if(fputs(recvline, stdout) == EOF)
            err_quit("fputs error", sum);
        sum++;
    }
    if (n < 0) {
        err_quit("read error", sum);
    }
    close(sockfd);
}
    printf("%d\n",sum);
    exit(0);
}
