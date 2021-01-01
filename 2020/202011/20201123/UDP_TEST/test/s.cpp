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
    addr.sin_port = htons(13333);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    while(1)
    {

    
    struct sockaddr_in peer_addr;
    socklen_t len = sizeof(peer_addr);
    char buf[1024]= {0};
    
    recvfrom(sockfd,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer_addr,&len);
    printf("cil:buf:%s,%d,%d\n",buf,peer_addr.sin_family,ntohs(peer_addr.sin_port));
    memset(buf,0,sizeof(buf));
    strcpy(buf,"i am svrer");
    
    sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&peer_addr,len);
    printf("svr:%s\n",buf);
    }
    close(sockfd);
    return 0;
}
