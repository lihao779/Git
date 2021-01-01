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
    addr.sin_port = htons(19998);
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");

    int ret = bind(listen_sock,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        close(listen_sock);
        return -1;
    }
    ret = listen(listen_sock,5);
    if(ret < 0)
    {
        perror("listen");
        close(listen_sock);
        return -1;
    }
    int sockfd = accept(listen_sock,NULL,NULL);
    while(1)
    {
        while(1)
        {

            sleep(1);
        }
        char buf[1024] = {0};
        recv(sockfd,buf,sizeof(buf)-1,0);
        sleep(1);
        memset(buf,0,sizeof(buf));
        strcpy(buf,"1");
        send(sockfd,buf,strlen(buf),0);
    }
    return 0;
}

