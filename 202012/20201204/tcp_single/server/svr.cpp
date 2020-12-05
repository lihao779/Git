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
    int listen_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_sock < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");

    int ret = bind(listen_sock,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        close(listen_sock);
        return -1;
    }
    ret = listen(listen_sock,1);
    if(ret < 0)
    {
        perror("listen");
        close(listen_sock);
        return -1;
    }
    int sockfd = accept(listen_sock,NULL,NULL);
    if(sockfd < 0)
    {
        perror("accept");
        close(listen_sock);
        return -1;
    }
    while(1)
    {

        char buf[1024] = {0};
        ret = recv(sockfd,buf,sizeof(buf)-1,0);
        if(ret < 0)
        {
            perror("recv");
            close(sockfd);
            close(listen_sock);
            return -1;
        }
        else if(ret == 0)
        {
            printf("cil sockfd shundown\n");
            close(sockfd);
            close(listen_sock);
            return 0;
        }
        printf("cli:%zu,%s\n",((struct Headsize*)buf)->head_size,buf+sizeof(struct Headsize));
        // printf("cli:%s\n",buf);
        memset(buf,0,sizeof(buf));
        printf("svr:");
        std::cin >> buf;
        struct Headsize ah;
        ah.head_size = strlen(buf);
        char* date = (char*) malloc(sizeof(struct Headsize)+strlen(buf));
        memcpy(date,&ah,sizeof(ah));
        memcpy(date+sizeof(ah),buf,strlen(buf));

        ret = send(sockfd,date,sizeof(ah)+strlen(buf),0);
        if(ret < 0)
        {
            perror("send");
            close(sockfd);
            close(listen_sock);
            return -1;
        }
        delete date;
        
    }
    close(sockfd);
    close(listen_sock);
    return 0;
}

