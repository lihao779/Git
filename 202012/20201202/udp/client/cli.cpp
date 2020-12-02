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
    struct sockaddr_in svr_addr;
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(19999);
    svr_addr.sin_addr.s_addr = inet_addr("192.168.40.131");
    while(1)
    {
        char buf[1024] = {0};
        printf("cli:");
        std::cin >> buf;
        
        int ret = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&svr_addr,sizeof(svr_addr));
        if(ret < 0)
        {
            perror("sendto");
            close(sockfd);
            return -1;
        }
        memset(buf,'\0',sizeof(buf));
        ret = recvfrom(sockfd,buf,sizeof(buf)-1,0,NULL,NULL);
        if(ret < 0)
        {
            close(sockfd);
            perror("recvfrom");
            return -1;
        }
        printf("svr:%s\n",buf);
    }
    return 0;
}
