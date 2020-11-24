#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    struct sockaddr_in svr;
    svr.sin_family = AF_INET;
    svr.sin_port = htons(13333);
    svr.sin_addr.s_addr = inet_addr("192.168.40.131");
    while(1)
    {
        char buf[1024] = {0};
        strcpy(buf,"i am cil");
        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&svr,sizeof(svr));
        printf("cil:%s\n",buf);
        memset(buf,0,sizeof(buf));
        recvfrom(sockfd,buf,sizeof(buf)-1,0,NULL,NULL);
        printf("svr:%s\n",buf);

    }
    close(sockfd);
    return 0;
}
