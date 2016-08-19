/*************************************************************************
	> File Name: str_server3.c
	> Author: 
	> Mail: 
	> Created Time: 2016年03月17日 星期四 16时01分50秒
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
#include<poll.h>

#define MAXLINE 100
#define LISTENQ 12

int main()
{
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd client[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = 5375;

    bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for (i = 1; i < OPEN_MAX; i++)
    {
        client[i].fd = -1;
    }
    maxi = 0;

    for ( ; ; )
    {
        nready = poll(client, maxi + 1, INFTIM);

        if (client[0].revents & POLLRDNORM)
        {
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

            for (i = 1; i < OPEN_MAX; i++)
            {
                if (client[i].fd < 0)
                {
                    client[i].fd = connfd;
                    break;
                }    
                if (i == OPEN_MAX)
                {
                    printf("too many clients!");
                    return 0;
                }
                
                client[i].events = POLLRDNORM;
                if (i > maxi)
                {
                    maxi = i;
                }
                if (--nready <= 0)
                {
                    continue;
                }
            }
        }

        for (i = 1; i <= maxi; i++)
        {
            if ((sockfd = client[i].fd) < 0)
            {
                continue;
            }
            if (client[i].revents & (POLLRDNORM | POLLERR))
            {
                if ( (n = read(sockfd, buf, MAXLINE)) < 0 )
                {
                    if (errno == ECONNRESET)
                    {
                        close(sockfd);
                        client[i].fd = -1;
                    }
                    else 
                    {
                        printf("read_error");
                        return 0;
                    }
                }
                else if (n == 0)
                {
                    close(sockfd);
                    client[i].fd = -1;
                }
                else 
                {
                    write(sockfd, buf, n);
                }
                if (--nready <= 0)
                {
                    break;
                }
            }
        }
    }
}
