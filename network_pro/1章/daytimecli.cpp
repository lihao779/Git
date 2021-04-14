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
    struct sockaddr_in servaddr, myaddr;
    socklen_t len;
    int sockfd, n;
    char recvline[MaxLine + 1];

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("create sockfd failed");
        exit(0);
    }
    
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    //servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("ip write error");
        exit(0);
    }
    
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect failed");
        exit(0);
    }
    
    len = sizeof(myaddr);
    getsockname(sockfd, (struct sockaddr*)&myaddr, &len);
    char buf[1024];
    printf("my ip:%s, port:%d\n",inet_ntop(AF_INET, &myaddr.sin_addr, buf, sizeof(buf)), ntohs(myaddr.sin_port));

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
