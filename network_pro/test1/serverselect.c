#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#define PORT 9000
#define LISTEN 5

int main()
{
    int listenfd;
    struct sockaddr_in svraddr;
    fd_set rset, allocset; 
    int maxfd;
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenfd < 0)
    {
        perror("socket error");
        exit(0);
    }

    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(PORT);
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(listenfd, (struct sockaddr*)&svraddr, sizeof(svraddr));
    if(ret < 0)
    {
        perror("bind error");
        close(listenfd);
        exit(0);
    }

    ret = listen(listenfd, LISTEN);
    if(ret < 0)
    {
        perror("listen error");
        close(listenfd);
        exit(0);
    }
    
    FD_ZERO(&rset);
    FD_SET(listenfd, &rset);
    maxfd = listenfd;
    for(; ;)
    {
        allocset = rset;
        int ret = select(maxfd + 1, &allocset, NULL, NULL, NULL);
        if(ret == 0)
        {
            printf("time out");
            continue;
        }
        else if(ret < 0)
        {
            perror("select error");
            return 0;
        }
        for(int i = listenfd + 1; i < maxfd + 1; i++)
        {
            char buf[1024] = {0};
            if(FD_ISSET(i, &allocset))
            {
                if(read(i, buf, sizeof(buf) - 1) == 0)
                {
                    close(i);
                    FD_CLR(i, &rset);
                    for(int j = maxfd; j >= 0; j--)
                    {
                        if(FD_ISSET(j, &rset))
                        {
                            maxfd = j;
                            break;
                        }
                    }
                    continue;
                }
                write(i, buf, strlen(buf));
            }
        }
        if(FD_ISSET(listenfd, &allocset))
        {
            int connfd = accept(listenfd, NULL, NULL);
            if(connfd > maxfd)
                maxfd = connfd;
            FD_SET(connfd, &rset);
        }
    }

}


