#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <iostream>



void* Startchat(void* arg)
{
    pthread_detach(pthread_self());
    int sockfd =*(int*)arg;
    char buf[1024] = {0};
    while(1)
    {
    int ret = recv(sockfd,buf,sizeof(buf)-1,0);
    if(ret < 0)
    {
        perror("recv");
        close(sockfd);
        delete(int*)arg;
        return NULL;
    }
    if(ret == 0)
    {
        printf("cli shutdown\n");
        close(sockfd);
        delete(int*)arg;
        return NULL;
    }
    printf("cli:%s\n",buf);
    printf("svr:");
    std::cin>>buf;
    ret = send(sockfd,buf,strlen(buf),0);
    if(ret < 0)
    {
        perror("send");
        close(sockfd);
        delete(int*)arg;
        return NULL;
    }
    }
    close(sockfd);
    delete(int*)arg;
    return NULL;

}

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
    ret = listen(listen_sockfd,5);
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
        pthread_t tid;
        
        int* newsockfd = new int(sockfd);
        ret = pthread_create(&tid,NULL,Startchat,newsockfd);
        if(ret < 0)
        {
            delete newsockfd;
            close(sockfd);
            close(listen_sockfd);
            perror("pthread_create");
            return -1;
        }
    }

    close(listen_sockfd);
    return 0;
}

