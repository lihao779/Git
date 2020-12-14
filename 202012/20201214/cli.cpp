#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <malloc.h>
#include "../App.hpp"
int main()
{
    
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in svr_addr;
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(19998);
    svr_addr.sin_addr.s_addr = inet_addr("192.168.40.131");
    int ret = connect(sockfd,(struct sockaddr*)&svr_addr,sizeof(svr_addr));
    if(ret < 0)
    {
        perror("connect");
        close(sockfd);
        return -1;
    }
    while(1)
    {
        printf("cli:");
        char buf[1024] = {0};
        strcpy(buf,"111");
        struct Headsize ah;
        ah.head_size = strlen(buf);
        char* date  = (char*)malloc(sizeof(ah)+strlen(buf));
        memcpy(date,&ah,sizeof(ah));
        memcpy(date+sizeof(ah),buf,strlen(buf));

        ret = send(sockfd,date,sizeof(ah)+strlen(buf),0);
        if(ret < 0)
        {
            perror("send");
            close(sockfd);
            return -1;
        }
        delete date;
        memset(buf,0,sizeof(buf));

        ret = recv(sockfd,buf,sizeof(buf)-1,0);
        if(ret < 0)
        {
            perror("recv");
            close(sockfd);
            return -1;
        }
        else if(ret == 0)
        {
            printf("svr sockfd shundown\n");
            close(sockfd);
            return 0;
        }
        printf("svr:%zu,%s\n",((struct Headsize*)buf)->head_size,buf+sizeof(struct Headsize));
    }
    close(sockfd);
    return 0;
}
