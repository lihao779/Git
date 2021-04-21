#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define SVRPORT  9000

void str_cli(FILE*, int);
void handler(int)
{
    printf("SIGPIPE\n");
}
int main(int argc, char* argv[])
{
    signal(SIGPIPE, handler);
    if(argc != 2)
    {
        printf("using: ./tcpcli <server_address>");
        exit(0);
    }

    int sockfd;
    struct sockaddr_in svraddr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("socket error");
        exit(0);
    }

    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(SVRPORT);
    inet_pton(AF_INET, argv[1], &svraddr.sin_addr);

    if(connect(sockfd, (struct sockaddr*)&svraddr, sizeof(svraddr)) < 0)
    {
        perror("connect error");
        close(sockfd);
        exit(0);
    }

    str_cli(stdin, sockfd);
    close(sockfd);

    return 0;
}

#define BUFSIZE 1024
void str_cli(FILE* pf, int sockfd)
{
    fd_set rset;
    FD_ZERO(&rset);
    char buf[BUFSIZE] = {0};
    int stdineof = 0;
    for(; ;)
    {
        if(stdineof == 0)
            FD_SET(fileno(pf), &rset);
        FD_SET(sockfd, &rset);
        int maxfd = (fileno(pf) > sockfd ? fileno(pf) : sockfd) + 1;
        int ret = select(maxfd, &rset, NULL ,NULL ,NULL);
        if(ret < 0)
        {
            perror("select error");
            return;
        }
        else if(ret == 0)
        {
            printf("time out");
            continue;
        }
        if(FD_ISSET(sockfd, &rset))
        {
            if(read(sockfd, buf, sizeof(buf) - 1) == 0)
            {
                if(stdineof == 1)
                    return;
                else
                {
                    perror("peer shutdown");
                    return;
                }
            }
            write(fileno(stdout), buf, strlen(buf));
            memset(buf, '\0', sizeof(buf));
        }
        if(FD_ISSET(fileno(pf), &rset))
        {
            if(read(fileno(pf), buf, sizeof(buf) - 1) == 0)
            {
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(pf), &rset);
                continue;
            }
            write(sockfd, buf, strlen(buf));
            memset(buf, '\0', sizeof(buf));
        }
    }
}







#if 0
#define BUFSIZE 1024
void str_cli(FILE* pf, int sockfd)
{
    fd_set rset;
    FD_ZERO(&rset);
    int maxfd = (fileno(pf) > sockfd ? fileno(pf) : sockfd);
    char sendbuf[BUFSIZE] = {0};
    char recvbuf[BUFSIZE] = {0};
    for(; ;)
    {
        FD_SET(fileno(pf), &rset);
        FD_SET(sockfd, &rset);
        int ret = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(ret == 0)
        {
            perror("time out");
            continue;
        }
        else if(ret < 0)
        {
            perror("select error");
            return;
        }
        if(FD_ISSET(fileno(pf), &rset))
        {
            if(NULL == fgets(sendbuf, sizeof(sendbuf) - 1, pf))
            {
                return;
            }
            if(write(sockfd, sendbuf, strlen(sendbuf)) < 0)
            {
                perror("write error");
                return;
            }
        }
        if(FD_ISSET(sockfd, &rset))
        {
            if(0 == read(sockfd, recvbuf, sizeof(recvbuf) - 1))
            {
                printf("peer shutdown\n");
                return ;
            }
            fputs(recvbuf, stdout);
        }
        memset(sendbuf, '\0', sizeof(sendbuf));
        memset(recvbuf, '\0', sizeof(recvbuf));

    }
}
#endif



#if 0
#define BUFSIZE 1024
void str_cli(FILE* pf, int sockfd)
{
    char sendbuf[BUFSIZE], recvbuf[BUFSIZE];
    while(fgets(sendbuf, sizeof(sendbuf) - 1, pf) != NULL)
    {
        write(sockfd, sendbuf, strlen(sendbuf));
        sleep(1);
        printf("111\n");
        write(sockfd, sendbuf, strlen(sendbuf));
        sleep(3);
        if(read(sockfd, recvbuf, sizeof(recvbuf)) == 0)
        {
            perror("read error");
            return ;
        }
        fputs(recvbuf, stdout);
        bzero(sendbuf, sizeof(sendbuf));
        bzero(recvbuf, sizeof(recvbuf));
    }
}
#endif
