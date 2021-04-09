#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
const size_t MaxLine = 1024;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("user: ./a.out <ipaddress>");
        exit(0);
    }
    struct sockaddr_in6 servaddr;
    int sockfd, n;
    char recvline[MaxLine + 1];

    if( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
    {
        printf("create sockfd failed");
        exit(0);
    }
    
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(13);
    //servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    if(inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
    {
        printf("ip write error");
        exit(0);
    }
    
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect failed");
        exit(0);
    }

    while( (n = read(sockfd, recvline, MaxLine)) > 0)
    {
        recvline[n] = '\0';
        if(fputs(recvline, stdout) == EOF)
        {
            printf("fputs error");
            exit(0);
        }
    }
    if(n < 0)
    {
        printf("read error");
        exit(0);
    }

    return 0;
}
