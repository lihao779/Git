#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

int main()
{
    int listen_sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr =inet_addr("0.0.0.0");

    int ret = bind(listen_sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        close(listen_sockfd);
        return -1;
    }
    ret = listen(listen_sockfd,1);
    if(ret < 0)
    {
        perror("listen");
        close(listen_sockfd);
        return -1;
    }
    while(1)
    {
        int sockfd = accept(listen_sockfd,NULL,NULL);
        if(sockfd < 0)
        {
            perror("accept");
            close(listen_sockfd);
            return -1;
        }
        pid_t pid = fork();
        if(pid < 0)
        {
            perror("fork");
            close(sockfd);
        }
        else if(pid > 0)
        {
            close(sockfd);
        }
        else 
        {
            close(listen_sockfd);
            while(1)
            {
                char buf[1024] = {0};
                ssize_t ret = recv(sockfd,buf,sizeof(buf)-1,0);
                if(ret < 0)
                {
                    perror("recv");
                    close(sockfd);
                    return -1;
                }
                else if(ret == 0)
                {
                    printf("client shundown\n");
                    close(sockfd);
                    return 0;
                }
                printf("cli:%s\n",buf);
                memset(buf,0,sizeof(buf));
                printf("svr:");
                std::cin >> buf;
                // strcpy(buf,"i am server");
                ret = send(sockfd,buf,strlen(buf),0);
                if(ret < 0)
                {
                    perror("send");
                    close(sockfd);
                    return -1;
                }
                // printf("svr:%s\n",buf);
            }
            close(sockfd);
        }
    }
    close(listen_sockfd);
    return 0;
}

