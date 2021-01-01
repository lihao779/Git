#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <iostream>

int sockfd;
void sigcb(int sign)
{
    char buf[1024] = {0};
    printf("SIGURG\n");
    int ret = recv(sockfd,buf,sizeof(buf)-1,MSG_OOB);
    printf("cli:%s\n",buf);
}

int main()
{
    signal(SIGURG,sigcb);
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
    sockfd = accept(listen_sock,NULL,NULL);
    if(sockfd < 0)
    {
        perror("accept");
        close(listen_sock);
        return -1;
    }
    fcntl(sockfd,F_SETOWN,getpid());
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
        printf("cli:%s\n",buf);
        memset(buf,0,sizeof(buf));
        printf("svr:");
        std::cin >> buf;
        ret = send(sockfd,buf,strlen(buf),0);
        if(ret < 0)
        {
            perror("send");
            close(sockfd);
            close(listen_sock);
            return -1;
        }
    }
    close(sockfd);
    close(listen_sock);
    return 0;
}

