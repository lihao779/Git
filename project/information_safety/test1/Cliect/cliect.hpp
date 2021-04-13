#pragma once
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include "../communion.hpp"



class Cli
{
    public:
        Cli(std::string ip, uint32_t port):ip_(ip), port_(port) {}
        
        bool Conn();
        int Register();
        int Login();
        
        
    private:
        std::string ip_;
        uint32_t port_;
        int sockfd_;
};

bool Cli::Conn()
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd_ <= 0)
        return false;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    int ret = connect(sockfd_, (struct sockaddr*)&addr, sizeof(addr));   
    if(ret < 0)
        return false;
    return true;
}

int Cli::Register()
{
    std::string nick_name;
    int passwd, temp;
    std::cout << "please input your nick_name:";
    std::cin >> nick_name;
    while(1)
    {
        std::cout << "please input your passwd:";
        std::cin >> passwd;
        std::cout << "please input your passwd again:";
        std::cin >> temp;
        if(passwd == temp)
            break;
        else 
            std::cout << "two passwd is not same, please enter passwd again" << std::endl;
    }
    
    User_info u(nick_name, passwd, REGISTER);
    int ret = send(sockfd_, &u, sizeof(u), 0);
    if(ret < 0)
    {
        std::cout << "send msg error" << std::endl;
    }
    int id = -1;
    ret = recv(sockfd_, &id, sizeof(id), 0);
    if(ret < 0)
    {
        std::cout << "send msg error" << std::endl;
    }
    else if(ret == 0)
    {
        std::cout << "server is shutdown" << std::endl;
        close(sockfd_);
    }
    std::cout << "your id is " << id << std::endl;
    return id;
}

int Cli::Login()
{

}
