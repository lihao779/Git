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
#include <poll.h>

#define PORT 9000
#define LISTEN 5
#define CLISIZE 1024
int main()
{
    int listenfd;
    struct sockaddr_in svraddr;
    struct pollfd cli[CLISIZE];
    int max;
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
    
    cli[0].fd = listenfd;
    cli[0].events = POLLRDNORM;
    for(int i = 1; i < CLISIZE; i++)
        cli[i].fd = -1;
    max = 0;

    for(; ;)
    {
        int nready = poll(cli, max + 1, -1);
        if(cli[0].revents & POLLRDNORM)
        {
            cli[0].revents = 0;
            int connfd = accept(cli[0].fd, NULL, NULL);
            int i;
            for(i = 1; i < CLISIZE; i++)
            {
                if(cli[i].fd < 0)
                {
                    cli[i].fd = connfd;
                    cli[i].events = POLLRDNORM;
                    if(i > max)
                        max = i;
                    break;
                }
            }
            if(i == CLISIZE)
            {
                printf("too many connect");
                continue;
            }
            if(--nready <= 0)
                continue;
        }
        for(int i = 1; i < max + 1; i++)
        {
            char buf[1024] = {0};
            if(cli[i].fd < 0)
                continue;
            if(cli[i].revents & (POLLRDNORM | POLLERR))
            {
                cli[i].revents = 0;
                int n;
                if((n = read(cli[i].fd, buf, sizeof(buf) - 1)) < 0)
                {
                    perror("read error");
                    close(cli[i].fd);
                    cli[i].fd = -1;
                    //max...
                    for(int j = max; j >= 0; j--)
                    {
                        if(cli[j].fd > 0)
                        {
                            max = j;
                            break;
                        }
                    }
                    continue;
                }
                else if(n == 0)
                {
                    printf("peer shutdown\n");
                    close(cli[i].fd);
                    cli[i].fd = -1;
                    //max...
                    for(int j = max; j >= 0; j--)
                    {
                        if(cli[j].fd > 0)
                        {
                            max = j;
                            break;
                        }
                    }
                    continue;
                }
                else
                    write(cli[i].fd, buf, n);
                if(--nready <= 0)
                    break;

            }
        }
    }

    return 0;
}


