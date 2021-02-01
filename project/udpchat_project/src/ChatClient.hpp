#pragma once
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#include "ConnectInfo.hpp"
#include "tools.hpp"
#include "UserManager.hpp"


struct MySelf
{
    MySelf()
    {
        nick_name_.clear();
        school_.clear();
        passwd_.clear();
    }
    std::string nick_name_;
    std::string school_;
    std::string passwd_;
    uint32_t user_id_;
};

class UdpClient
{
    public:
    UdpClient(const std::string& ip)
        :tcp_sock_(-1)
         ,udp_sock_(-1)
         ,ip_(ip)
    {
    }
    ~UdpClient()
    {}

    int CreateUdpSock();
    int RegistertoSvr();
    int LogtoSvr();
    int SendUdpMsg(const std::string& msg);
    int RecvUdpMsg(std::string* recvmsg);
    void CloseFd();
    MySelf& GetMe();

    private:
    int CreateTCPSock();
    int ConnecttoSvr();
    private:
        int tcp_sock_;
        int udp_sock_;
        MySelf me_;
        std::string ip_;
};
int UdpClient::CreateTCPSock()
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
int UdpClient::CreateUdpSock()
{
    udp_sock_ = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(udp_sock_ < 0)
    {
        LOG(ERROR,"创建客户端udp_sock失败")<<std::endl;
        return -1;
    }
    return 0;
}
int UdpClient::ConnecttoSvr()
{
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(TCP_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    int ret = connect(tcp_sock_,(struct sockaddr*)&dest_addr,sizeof(dest_addr));
    if(ret < 0)
    {
        LOG(ERROR,"客户端连接服务端失败")<<std::endl;
        return -1;
    }
    return 0;
}
int UdpClient::RegistertoSvr()
{
    int ret = CreateTCPSock();
    if(ret < 0)
    {
        return -1;
    }
    ret = ConnecttoSvr();
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
        CloseFd();
        return -1;
    }
    if(reply_info.resp_status_ == REGISTER_FAILED)
    {
        LOG(ERROR,"客户端注册失败") << std::endl;
        return -1;
    }
    me_.nick_name_ = ri.nick_name_;
    me_.passwd_ = ri.passwd_;
    me_.school_ = ri.school_;
    me_.user_id_ = reply_info.id_;
    LOG(INFO,"客户端注册成功") << "  [id:" << me_.user_id_ << "]" <<std::endl;
    return 0;
}
int UdpClient::LogtoSvr()
{
    int ret = CreateTCPSock();
    if(ret < 0)
        return -1;
    ret = ConnecttoSvr();
    if(ret < 0)
        return -1;
    char type = LOGIN_RESQ;
    ssize_t send_size = send(tcp_sock_,&type,1,0);
    if(send_size < 0)
    {
        LOG(ERROR,"发送登录请求失败") << std::endl;
        return -1;
    }
    struct LoginInfo ri;
    ri.id_ = me_.user_id_;
    strncpy(ri.passwd_,me_.passwd_.c_str(),sizeof(ri.passwd_));
    send_size = send(tcp_sock_,&ri,sizeof(ri),0);
    if(send_size < 0)
    {
        LOG(ERROR,"发送登录请求失败") << std::endl;
        return -1;
    }

    struct ReplyInfo reply_info;
    int recv_size = recv(tcp_sock_,&reply_info,sizeof(reply_info),0);
    if(recv_size < 0)
    {
        LOG(ERROR,"接收登录请求失败") <<std::endl;
        return -1;
    }
    else if(recv_size == 0)
    {
        LOG(ERROR,"接收登录请求失败") <<std::endl;
        CloseFd();
        return -1;
    }
    if(reply_info.resp_status_ != LOGIN_SUCCESS)
    {
        LOG(ERROR,"登陆失败") << std::endl;
        return -1;
    }
    LOG(INFO,"登陆成功") << std::endl;
    return 0;

}
void UdpClient::CloseFd()
{
    if(tcp_sock_ > 0)
    {
        close(tcp_sock_);
        tcp_sock_ = -1;
    }
}
int UdpClient::SendUdpMsg(const std::string& msg)
{

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(UDP_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    socklen_t dest_addrlen = sizeof(dest_addr);

    int udpsend_max = UDPSEND_MAX;
    while(udpsend_max--)
    {
        int ret = sendto(udp_sock_,msg.c_str(),msg.size(),0,(struct sockaddr*)&dest_addr,dest_addrlen);
        if(ret < 0)
        {
            LOG(ERROR,"客户端发送消息失败") << std::endl;
        }
        else
        {
            return 0;
        }
    }
    return -1;
}
int UdpClient::RecvUdpMsg(std::string* recvmsg)
{
    char buf[UDP_MAX_DATE] = {0};
    int ret = recvfrom(udp_sock_,buf,sizeof(buf) - 1,0,NULL,NULL);
    if(ret < 0)
    {
        LOG(ERROR,"客户端接收消息失败") << std::endl;
        return -1;
    }
    (*recvmsg).assign(buf,strlen(buf));
    return 0;

}
MySelf& UdpClient::GetMe()
{
    return me_;
}
