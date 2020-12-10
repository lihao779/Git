#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define PORT 8080


int main()
{
    int listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listenfd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    
    int ret = bind(listenfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        close(listenfd);
        return -1;
    }
    ret = listen(listenfd,1);
    if(ret < 0)
    {
        perror("listen");
        close(listenfd);
        return -1;
    }

    sleep(15);
    printf("i will accept one\n");
    accept(listenfd,NULL,NULL);
    
    sleep(10);
    printf("i will accept one\n");
    accept(listenfd,NULL,NULL);

    sleep(10);
    printf("i will accept one\n");
    accept(listenfd,NULL,NULL);



    while(1)
    {
        sleep(1);
    }
    
    return 0;
}
