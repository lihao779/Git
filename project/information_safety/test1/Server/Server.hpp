#pragma once
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include "../communion.hpp"


const uint32_t port = 9000;
const size_t thread_count = 3;
struct User
{
    User() = default;
    User(std::string nick_name, int passwd)
        :nick_name_(nick_name), passwd_(passwd)
    {}
    std::string nick_name_;
    int passwd_;
};

class Manage_User
{
    public:
        
        Manage_User() { data_.clear(); pthread_mutex_init(&mut_, NULL);}
        ~Manage_User() { pthread_mutex_destroy(&mut_); }
        int AddUser(const User&);
        int DelUser(int id);
    private:
        std::unordered_map<int, User> data_;
        int pare_id = 100;
        pthread_mutex_t mut_;

};

int Manage_User::AddUser(const User& u)
{
   pthread_mutex_lock(&mut_);
   int id = pare_id;
   data_.insert({pare_id++, u}); 
   pthread_mutex_unlock(&mut_);
   return id;
}

int Manage_User::DelUser(int id)
{
    pthread_mutex_lock(&mut_);
    auto it = data_.find(id);
    if(it == data_.end())
    {
        pthread_mutex_unlock(&mut_);
        return -1;
    }
    data_.erase(it);
    pthread_mutex_unlock(&mut_);
    return 1;
}

class Ser
{
    public:
        Ser() {}
        ~Ser() { close(listen_sockfd_);}
        int InitFd();
        int CreateThread();
    private:
        static void* work_thread(void* arg);
    private:
        int listen_sockfd_;
        Manage_User man_user_;
};

int Ser::InitFd()
{
    listen_sockfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listen_sockfd_ < 0)
    {
        std::cout << "create listen_sock failed" << std::endl; 
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");
    addr.sin_port = htons(port);
    int ret = bind(listen_sockfd_, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        std::cout << "bind listen_sock failed" << std::endl; 
        return -1;
    }
    ret = listen(listen_sockfd_, 5);
    if(ret < 0)
    {
        std::cout << "listen listen_sock failed" << std::endl; 
        return -1;
    }
    return 1;
}
int Ser::CreateThread()
{
    pthread_t tid;
    for(size_t i = 0; i < thread_count; i++)
        pthread_create(&tid, NULL, work_thread, this);
    return 0;
}

void* Ser::work_thread(void* arg)
{
    pthread_detach(pthread_self());
    Ser* s = (Ser*)arg;
    while(1)
    {
        int sockfd = accept(s->listen_sockfd_, NULL , NULL);
        if(sockfd < 0)
        {
            std::cout << "accept sockfd failed" << std::endl;
            pthread_exit(NULL);
        }
        while(1)
        {
            struct User_info u;
            int ret = recv(sockfd, &u, sizeof(struct User_info), 0);
            if(ret == 0)
            {
                close(sockfd);
                break;
            }
            else if(ret < 0)
            {
                std::cout << "recv msg failed" << std::endl;
                continue;
            }
            //TODO
            std::cout << "nick_name:" << u.nick_name_ << " passwd:" << u.passwd_ << std::endl;
        }
    }
    return NULL;
}
