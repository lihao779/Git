#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

int main()
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");
    int ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        close(sockfd);
        return -1;
    }
    while(1)
    {
        char buf[1024] = {0};
        struct sockaddr_in peer_addr;
        socklen_t len = sizeof(peer_addr);
        ret = recvfrom(sockfd,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer_addr,&len);
        if(ret < 0)
        {
            perror("recvfrom");
            close(sockfd);
            return -1;
        }
        printf("cli:%s\n",buf);
        memset(buf,'\0',sizeof(buf));
        printf("svr:");
        std::cin >> buf;
        ret = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&peer_addr,len);
        if(ret < 0)
        {
            close(sockfd);
            perror("sendto");
            return -1;
        }
    }
    return 0;
}
