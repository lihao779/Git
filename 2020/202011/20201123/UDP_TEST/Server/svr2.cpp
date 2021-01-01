#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");
    int bind_return = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(bind_return < 0)
    {
        perror("bind");
        return -1;
    }
    while(1)
    {
    char buf[1024] = {0};
    struct sockaddr_in peer_addr;
    socklen_t peer_len  = sizeof(peer_addr);// 7;//sizeof(peer_addr);
    //7以上都可以，以下都不行
    recvfrom(sockfd,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer_addr,&peer_len);
    printf("cil:%s\n",buf);
    printf("addr.sin_family:%d,peer_len:%d,port:%d,\n",peer_addr.sin_family,peer_len,ntohs(peer_addr.sin_port));
    memset(buf,0,sizeof(buf));
    strcpy(buf,"i am svr");
    sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&peer_addr,peer_len);
    printf("srv:%s\n",buf);
    }
    close(sockfd);
    return 0;
}
