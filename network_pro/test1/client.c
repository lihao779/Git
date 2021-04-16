#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>


#define SVRPORT  20

void str_cli(FILE*, int);
int main(int argc, char* argv[])
{

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
    char sendbuf[BUFSIZE], recvbuf[BUFSIZE];
    while(fgets(sendbuf, sizeof(sendbuf) - 1, pf) != NULL)
    {
        write(sockfd, sendbuf, strlen(sendbuf));

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
