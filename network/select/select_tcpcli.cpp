#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("sockfd");
        exit(-1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");
    int ret = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("connect");
        exit(-1);
    }
    while(1)
    {
        char buf[1024] = "i am client1";

        int ret = send(sockfd,buf,strlen(buf),0);
        if(ret < 0)
        {
            perror("send");
            exit(-1);
        }
        sleep(1);
    }
    return 0;
}

