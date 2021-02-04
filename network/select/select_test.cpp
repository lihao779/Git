#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0)
    {
        printf("ERROR");
        exit(0);

    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(19999);
    int ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        printf("ERROR");
        exit(0);
    }
    listen(sockfd,5);


    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0,&readfds);
    FD_SET(sockfd,&readfds);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    ret = select(sockfd + 1,&readfds,NULL,NULL,&tv);
    printf("ret = %d\n",ret);
    if(ret < 0)
    {
        printf("ERROT\n");
        exit(0);
    }

    char buf[1024] = {0};
    if(FD_ISSET(0,&readfds)) 
    {
        read(0,buf,sizeof(buf) - 1);
        printf("buf is %s",buf);
    }
    else
    {
        printf("0fd is not in\n");
    }
    if(FD_ISSET(sockfd,&readfds)) 
    {
        printf("sockfd is in\n");
    }
    else
    {
        printf("sockfd is not in\n");
    }
    return 0;
}
