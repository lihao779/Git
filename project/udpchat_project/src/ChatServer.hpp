#pragma once

#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include <string>

#include "ConnectInfo.hpp"
#include "tools.hpp"
#include "UserManager.hpp"

#define TCP_PORT 17878


class TcpConnect
{
    public:
        TcpConnect()
            :new_sock_(-1)
             ,server_(nullptr)
        {}
        ~TcpConnect()
        {}

        void SetScokfd(int fd);
        int GetScokfd();
        void SetServer(void* server);
        void* GetServer();
    private:
        int new_sock_;
        void* server_;//保存ChatServer的this指针
};
void TcpConnect::SetScokfd(int fd)
{
    new_sock_ = fd;
}
int TcpConnect::GetScokfd()
{
    return new_sock_;
}
void TcpConnect::SetServer(void* server)
{
    server_ = server;
}
void* TcpConnect::GetServer()
{
    return server_;
}



class ChatServer
{
    public:
        ChatServer()
        {
            tcp_sock_ = -1;
            user_manager_ = nullptr;
        }
        ~ChatServer()
        {
            delete user_manager_;
        }


        
        int InitSvr(uint16_t tcp_port = TCP_PORT); // 初始化变量接口
        int Start(); // 启动线程 --udp(消息池中的生产&消费线程) --tcp(登陆&注册线程)


    private:
        static void* LoginRegisterStart(void* arg); //登陆注册线程入口
        static int DealRegister(TcpConnect* tc); //处理注册
        static int DealLogin(TcpConnect* tc); //处理登录
    private:
        int tcp_sock_;
        int udp_sock_;
        UserManage* user_manager_; 
};





int ChatServer::InitSvr(uint16_t tcp_port)
{
    //创建tcp_sock_
    tcp_sock_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(tcp_sock_ < 0)
    {
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(tcp_port);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(tcp_sock_,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        return -2;
    }
    ret = listen(tcp_sock_,5);
    if(ret < 0)
    {
        return -3;
    }
    //创建用户管理模块的实例化指针
    user_manager_ = new UserManage(); 
    if(!user_manager_)
    {
        LOG(ERROR,"创建用户管理模块");
        return -1;
    }
    // 暂时没考虑udp，登陆注册模块，消息池模块
    
    return 0;
}

/*
 * udp线程
 *  生产线程：从udp中读取数据并放入消息池
 *  消费线程：负责从消息池中拿数据发送给在线客户
 * tcp线程
 *  注册线程：注册并返回ID
 *  登陆线程：登录并返回登陆成功
 */
int ChatServer::Start()
{
    struct sockaddr_in peer_addr;
    socklen_t peer_addrlen = sizeof(peer_addr);
    while(1)
    {
        
        int new_sock = accept(tcp_sock_,(struct sockaddr*)&peer_addr,&peer_addrlen);
        if(new_sock < 0)
        {
            continue;
        }
        TcpConnect* tc = new TcpConnect();
        tc->SetScokfd(new_sock);
        tc->SetServer((void*)this);

        pthread_t tid;
        int ret = pthread_create(&tid,NULL,LoginRegisterStart,(void*)tc);
        
    }
}
void* ChatServer::LoginRegisterStart(void* arg)
{
    pthread_detach(pthread_self());

    TcpConnect* tc = (TcpConnect*)arg;

    char ques_type = -1;
    ssize_t recv_size = recv(tc->GetScokfd(),&ques_type,1,0);
    if(recv_size < 0)
    {
        close(tc->GetScokfd());
        delete tc;
        return NULL;
    }
    else if(recv_size == 0)
    {
        close(tc->GetScokfd());
        delete tc;
        return NULL;
    }
    switch(ques_type)
    {
        case REGISTER_RESQ:
        {
           if(DealRegister(tc) < 0)
           {
               delete tc;
               return NULL;
           }
            break;
        }
        case LOGIN_RESQ:
        {  
            if(DealLogin(tc) < 0)
            {
                delete tc;
                return NULL;
            }
            break;
        }
    }
    //返回用户:注册成功||登录成功
    //TODO
    close(tc->GetScokfd());
    delete tc;
    return NULL;
}
int ChatServer::DealRegister(TcpConnect* tc)
{
    ChatServer* cs = (ChatServer*)tc->GetServer();
    struct RegisterInfo ri;
    ssize_t recv_size = recv(tc->GetScokfd(),&ri,sizeof(ri),0);
    if(recv_size < 0)
    {
        close(tc->GetScokfd());
        return -1;
    }
    else if(recv_size == 0)
    {
        close(tc->GetScokfd());
        return -2;
    }
    //插入用户管理模块
    cs->user_manager_->DealRegister(ri.nick_name_,ri.school_,ri.passwd_);
    

    return 0;
}
int ChatServer::DealLogin(TcpConnect* tc)
{
    struct LoginInfo li;
    ssize_t recv_size = recv(tc->GetScokfd(),&li,sizeof(li),0);
    if(recv_size < 0)
    {
        close(tc->GetScokfd());
        return -1;
    }
    else if(recv_size == 0)
    {
        close(tc->GetScokfd());
        return -2;
    }
    //TODO
    
    return 0;
}
