#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define pthreadnum 10

struct sockaddr_in addr;

void* func(void* arg)
{
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return NULL;
    }
    connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    while(1)
    {}
    return NULL;
}


int main()
{
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");


    pthread_t tid[pthreadnum];
    for(int i = 0;i<pthreadnum;i++)
    {
        pthread_create(&tid[i],NULL,func,NULL);
    }

    for(int i = 0;i<pthreadnum;i++)
    {
        pthread_join(tid[i],NULL);
    }
    return 0;
}
