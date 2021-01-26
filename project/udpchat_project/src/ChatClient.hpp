#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#include "ConnectInfo.hpp"
#include "tools.hpp"


class MySelf
{
    std::string nick_name_;
    std::string school_;
    std::string passwd_;
    uint32_t user_id_;
};

class UdpClient
{
    public:
    UdpClient()
        :tcp_sock_(-1)
    {}
    ~UdpClient()
    {}

    int CreateSock();
    int ConnecttoSvr(const std::string& ip);
    int RegistertoSvr(const std::string& ip);

    private:
        int tcp_sock_;
};
int UdpClient::CreateSock()
{
    tcp_sock_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(tcp_sock_ < 0)
    {
        LOG(ERROR,"创建客户端tcp_sock失败")<<std::endl;
        return -1;
    }
    //客户端不推荐绑定
    return 0;
}
int UdpClient::ConnecttoSvr(const std::string& ip)
{
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(TCP_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    int ret = connect(tcp_sock_,(struct sockaddr*)&dest_addr,sizeof(dest_addr));
    if(ret < 0)
    {
        LOG(ERROR,"客户端连接服务端失败")<<std::endl;
        return -1;
    }
    return 0;
}
int UdpClient::RegistertoSvr(const std::string& ip)
{
    int ret = CreateSock();
    if(ret < 0)
        return -1;
    ret = ConnecttoSvr(ip);
    if(ret < 0)
        return -1;
    char type = REGISTER_RESQ;
    ssize_t send_size = send(tcp_sock_,&type,1,0);
    if(send_size < 0)
    {
        return -1;
    }
    struct RegisterInfo ri;

    std::cout << "please enter nick_name:";
    fflush(stdout);
    std::cin >> ri.nick_name_;
    std::cout << "please enter school:";
    fflush(stdout);
    std::cin >> ri.school_;
    while(1)
    {
        std::string first_passwd;
        std::string second_passwd;
        std::cout << "please enter your passwd:";
        fflush(stdout);
        std::cin >> first_passwd;
        std::cout << "please retry your passwd:";
        fflush(stdout);
        std::cin >> second_passwd;
        if(first_passwd == second_passwd)
        {
            strncpy(ri.passwd_,first_passwd.c_str(),first_passwd.size());
            break;
        }
        std::cout << "two enter passwd is not same" << std::endl;
    }
    ret = send(tcp_sock_,&ri,sizeof(ri),0);
    if(ret < 0)
    {
        LOG(ERROR,"客户端发送注册包失败") << std::endl;
        return -1;
    }
    ReplyInfo reply_info;
    ssize_t recv_size = recv(tcp_sock_,&reply_info,sizeof(reply_info),0);
    if(recv_size < 0)
    {
        LOG(ERROR,"客户端接收回复失败") << std::endl;
        return -1;
    }
    else if(recv_size == 0)
    {
        LOG(ERROR,"服务端已经关闭掉连接") << std::endl;
        return -1;
    }
    if(reply_info.resp_status_ == REGISTER_FAILED)
    {
        LOG(ERROR,"客户端注册失败") << std::endl;
        return -1;
    }
    LOG(INFO,"客户端注册成功") << std::endl;
    return 0;
}
