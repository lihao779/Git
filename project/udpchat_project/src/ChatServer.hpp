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
#include "MessagePool.hpp"


#define MAX_ROUND_COUNT 10
#define PTHREAD_COUNT 1

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
            udp_sock_ = -1;
            user_manager_ = nullptr;
            msg_pool_ = nullptr;
            memset(con_tid_,'\0',sizeof(pthread_t)*PTHREAD_COUNT);
            memset(pro_tid_,'\0',sizeof(pthread_t)*PTHREAD_COUNT);
        }
        ~ChatServer()
        {
            if(user_manager_)
            {
                delete user_manager_;
                user_manager_ = nullptr;
            }
            if(msg_pool_)
            {
                delete msg_pool_;
                msg_pool_ = nullptr;
            }
        }


        
        int InitSvr(uint16_t tcp_port = TCP_PORT,uint16_t udp_port = UDP_PORT); // 初始化变量接口
        int Start(); // 启动线程 --udp(消息池中的生产&消费线程) --tcp(登陆&注册线程)


    private:
        static void* LoginRegisterStart(void* arg); //登陆注册线程入口
        int DealRegister(TcpConnect* tc,uint32_t* user_id); //处理注册
        int DealLogin(TcpConnect* tc,uint32_t* user_id); //处理登录
        static void* ProductStart(void* arg); //消费线程
        static void* ConsumeStart(void* arg); //生产线程
        int RecvMsg();
        int SendMsg();
        int SendUdpMsg(std::string& msg,struct sockaddr_in addr,socklen_t addrlen);
    private:
        int tcp_sock_;
        int udp_sock_;
        UserManage* user_manager_; 
        MsgPool* msg_pool_; 
        //udp线程的标识符数组
        pthread_t con_tid_[PTHREAD_COUNT];
        pthread_t pro_tid_[PTHREAD_COUNT];
};





int ChatServer::InitSvr(uint16_t tcp_port,uint16_t udp_port)
{
    //创建tcp_sock_
    tcp_sock_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(tcp_sock_ < 0)
    {
        return -1;
    }
    struct sockaddr_in tcp_addr;
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(tcp_port);
    tcp_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(tcp_sock_,(struct sockaddr*)&tcp_addr,sizeof(tcp_addr));
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
        LOG(ERROR,"创建用户管理模块失败") << std::endl;
        return -1;
    }
    msg_pool_ = new MsgPool();
    if(!msg_pool_)
    {
        LOG(ERROR,"创建消息池失败") << std::endl;
        return -1;
    }
    // 创建udp_sock
    udp_sock_ = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(udp_sock_ < 0)
    {
        LOG(ERROR,"udp_sock创建失败") << std::endl;
        return -1;
    }
    struct sockaddr_in udp_addr;
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(udp_port);
    udp_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    ret = bind(udp_sock_,(struct sockaddr*)&udp_addr,sizeof(udp_addr));
    if(ret < 0)
    {
        LOG(ERROR,"udp_sock绑定失败") << std::endl;
        return -2;
    }
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
    //创建udp线程
    for(int i = 0;i < PTHREAD_COUNT;i++)
    {
        int ret = pthread_create(&con_tid_[i],NULL,ConsumeStart,this);
        if(ret < 0)
        {
            LOG(ERROR,"消费线程创建失败") << std::endl;
            return -1;
        }
        ret = pthread_create(&pro_tid_[i],NULL,ProductStart,this);
        if(ret < 0)
        {
            LOG(ERROR,"生产线程创建失败") << std::endl;
            return -1;
        }
    }


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
        if(ret < 0)
        {
            close(tc->GetScokfd());
            delete tc;
            tc = nullptr;
        }
    }
}
void* ChatServer::LoginRegisterStart(void* arg)
{
    pthread_detach(pthread_self());

    TcpConnect* tc = (TcpConnect*)arg;
    ChatServer* cs = (ChatServer*)tc->GetServer();

    char ques_type = -1;
    ssize_t recv_size = recv(tc->GetScokfd(),&ques_type,1,0);
    if(recv_size < 0)
    {
        close(tc->GetScokfd());
        delete tc;
        tc = nullptr;
        return nullptr;
    }
    else if(recv_size == 0)
    {
        close(tc->GetScokfd());
        delete tc;
        tc = nullptr;
        return nullptr;
    }
    int resp_status = -1;
    uint32_t user_id = -1;
    switch(ques_type)
    {
        case REGISTER_RESQ:
        {
            resp_status = cs->DealRegister(tc,&user_id);
            break;
        }
        case LOGIN_RESQ:
        {  
            resp_status = cs->DealLogin(tc,&user_id);
            break;
        }
    }
    //返回用户:注册成功||登录成功
    //struct RelpyInfo
    
    struct ReplyInfo ri;
    ri.resp_status_ = resp_status;
    ri.id_ = user_id; 
    
    LOG(INFO,"服务端注册或者登录完毕")<<"status:"<<resp_status<<std::endl;
    std::cout<<"注册id:"<<user_id<<std::endl;
    
    int max_round_count = MAX_ROUND_COUNT;
    while(max_round_count--)
    {
        ssize_t send_size = send(tc->GetScokfd(),&ri,sizeof(ri),0);
        if(send_size < 0)
        {
            LOG(WARNING,"服务端回复注册或者登陆失败")<<std::endl;
        }
        else
        {
            LOG(INFO,"服务端回复注册或者登陆成功")<<std::endl;
            break;
        }
    }
    close(tc->GetScokfd());
    delete tc;
    tc = nullptr;
    return nullptr;
}
int ChatServer::DealRegister(TcpConnect* tc,uint32_t* user_id)
{
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
    int ret = user_manager_->DealRegister(ri.nick_name_,ri.school_,ri.passwd_,user_id);
    if(ret < 0)
    {
        return REGISTER_FAILED;
    }
    return REGISTER_SUCCESS;
}
int ChatServer::DealLogin(TcpConnect* tc,uint32_t* user_id)
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
    *user_id = li.id_;
    //接收成功
    int ret = user_manager_->DealLogin(li.id_,li.passwd_);
    if(ret < 0)
    {
        return LOGIN_FAILED;
    }
    return LOGIN_SUCCESS;
}

void* ChatServer::ProductStart(void* arg)
{
    pthread_detach(pthread_self());    
    ChatServer* cs = (ChatServer*)arg;
    while(1)
    {
        cs->RecvMsg();
    }
}
void* ChatServer::ConsumeStart(void* arg)
{
    pthread_detach(pthread_self());    
    ChatServer* cs = (ChatServer*)arg;
    while(1)
    {
        cs->SendMsg();
    }
}
int ChatServer::RecvMsg()
{
    //1.接收数据
    //2.放入消息池
    char buf[UDP_MAX_DATE] = {0};
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int recv_size = recvfrom(udp_sock_,buf,sizeof(buf)-1,0,(struct sockaddr*)&addr,&addrlen);
    if(recv_size < 0)
    {
        return -1;
    }
    UdpMsg um;
    std::string msg;
    msg.assign(buf,strlen(buf));
    um.deserialize(msg);
    if(user_manager_->IsLog(um.Get_id(),addr,addrlen) < 0)
    {
        return -1;
    }
    msg_pool_->PushMsg(msg);
    return 0;
}
int ChatServer::SendMsg()
{
    //1.从消息池中读取数据
    //2.发送给在线用户
    std::string msg;
    msg_pool_->PopMsg(&msg);
    
    std::vector<UserInfo> online_user;
    user_manager_->GetOnlineUer(&online_user); 

    for(size_t i = 0;i < online_user.size();i++)
    {
        int ret = SendUdpMsg(msg,online_user[i].GetUserAddr(),online_user[i].GetUserAddrlen());
        if(ret < 0)
        {
            LOG(ERROR,"发送数据失败") << std::endl;
            return -1;
        }
    }
    return 0;
}
int ChatServer::SendUdpMsg(std::string& msg,struct sockaddr_in addr,socklen_t addrlen)
{
    int udpsend_max = UDPSEND_MAX;
    while(udpsend_max--)
    {
        int send_size = sendto(udp_sock_,msg.c_str(),msg.size(),0,(struct sockaddr*)&addr,addrlen);
        if(send_size < 0)
        {
            LOG(ERROR,"发送消息败") << " ip is" <<inet_ntoa(addr.sin_addr) << " port is" << ntohs(addr.sin_port) << std::endl;
        }
        else
        {
            return 0;
        }
    }
    return -1;
}
