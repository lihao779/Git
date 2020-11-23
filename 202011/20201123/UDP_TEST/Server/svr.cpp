#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
int main()
{
    //创建套接字
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd<0)
    {
        perror("socket");
        return -1;
    }
    //绑定
    struct sockaddr_in addr; 
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1999);
    //addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");

    int bind_return = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(bind_return<0)
    {
        perror("bind");
        return -1;
    }
    while(1)
    {
      //接收消息
      char buf[1024] = {0};
      struct sockaddr peer_addr;
      socklen_t peer_len;
      ssize_t recv_size = recvfrom(sockfd,buf,sizeof(buf)-1,0,&peer_addr,&peer_len);
      if(recv_size<0)
      {
          perror("recvfrom");
          return -1;
      }
      printf("client:%s\n",buf);
      memset(buf,0,sizeof(buf));
        
      
      printf("server:");
      fflush(stdout);
      std::cin>>buf;
      //回复消息
      ssize_t send_size = sendto(sockfd,&buf,strlen(buf),0,&peer_addr,peer_len);
      if(send_size<0)
      {
          perror("sendto");
          return -1;
      }
    }
    close(sockfd);
    return 0;
}
