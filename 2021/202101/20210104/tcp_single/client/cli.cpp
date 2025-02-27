#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

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
    svr_addr.sin_port = htons(19999);
    svr_addr.sin_addr.s_addr = inet_addr("192.168.40.131");
    int ret = connect(sockfd,(struct sockaddr*)&svr_addr,sizeof(svr_addr));
    if(ret < 0)
    {
        perror("connect");
        close(sockfd);
        return -1;
    }
    int count = 1;
    while(1)
    {
        printf("cli:i---");
        char buf[1024] = {0};
        //std::cin >> buf;
        strcpy(buf,"i");
        ret = send(sockfd,buf,strlen(buf),0);
        if(ret < 0)
        {
            perror("send");
            close(sockfd);
            return -1;
        }
        printf("count:%d\n",count++);
        /*
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
        printf("svr:%s\n",buf);
        */
    }
    close(sockfd);
    return 0;
}
