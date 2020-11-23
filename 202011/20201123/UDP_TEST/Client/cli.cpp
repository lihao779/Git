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
    while(1)
    {
	//发送消息
      char buf[1024] = {0};
      printf("cli:");
      std::cin>>buf;
      struct sockaddr_in svr_addr;
      svr_addr.sin_family = AF_INET;
      svr_addr.sin_port = htons(1999);
      svr_addr.sin_addr.s_addr = inet_addr("192.168.40.131");
      int send_size = sendto(sockfd,&buf,strlen(buf),0,(struct sockaddr*)&svr_addr,sizeof(svr_addr));
      if(send_size<0)
      {
          perror("sendto");
          return -1;
      }
      memset(buf,0,sizeof(buf));
      int recv_size = recvfrom(sockfd,&buf,sizeof(buf)-1,0,NULL,NULL);
      if(recv_size<0)
      {
          perror("recvfrom");
          return -1;
      }
      printf("server:%s\n",buf);
       
    }
    close(sockfd);
    return 0;
}
