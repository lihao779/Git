#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace  std;
class UdpApi
{
    public:
        UdpApi()
        {
            sockfd_ = -1;
            peer_addrlen = sizeof(peer_addr);
        }
        // 创建套接字
        int CreateSock()
        {
            sockfd_ = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
            if(sockfd_ < 0)
            {
                perror("socket");
                return -1;
            }
            return 0;
        }
        // 绑定套接字
        int IP_Port_bind(const char* ip,uint16_t port)
        {
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip);
            int bind_return = bind(sockfd_,(struct sockaddr*)&addr,sizeof(addr));
            if(bind_return < 0)
            {
                perror("bind");
                return -1;
            }
            return 0;
        }       
        // 发送消息
        int Send_message_svr(const char* str)
        {
            int ret = sendto(sockfd_,str,strlen(str),0,(struct sockaddr*)&peer_addr,sizeof(peer_addr));
            if(ret < 0)
            {
                perror("send");
                return -1;
            }
            return 0;
        }
        // 接受消息
        int Recv_message_svr(char* str,int len)
        {
            int ret = recvfrom(sockfd_,str,len - 1 ,0,(struct sockaddr*)&peer_addr,&peer_addrlen);
            if(ret < 0)
            {
                perror("recvfrom");
                return -1;
            }
            return 0;
        }
        void IP_Port_cil(const char* ip,uint16_t port)
        {
            addr_cil.sin_family = AF_INET;
            addr_cil.sin_port = htons(port);
            addr_cil.sin_addr.s_addr = inet_addr(ip);

        }
        int Send_message_cil(const char* str)
        {
            int ret = sendto(sockfd_,str,strlen(str),0,(struct sockaddr*)&addr_cil,sizeof(addr));
            if(ret < 0)
            {
                perror("send");
                return -1;
            }
            return 0;
        }
        // 接受消息
        int Recv_message_cil(char* str,int len)
        {
            int ret = recvfrom(sockfd_,str,len-1,0,NULL,NULL);
            if(ret < 0)
            {
                perror("recvfrom");
                return -1;
            }
            return 0;
        }
        ~UdpApi()
        {
            close(sockfd_);
        }
    private:
        int sockfd_;
        struct sockaddr_in addr;//服务端绑定addr
        struct sockaddr_in peer_addr;//服务端对应的客户端
        
        struct sockaddr_in addr_cil;//客户端对应的服务端
        socklen_t peer_addrlen;
};
