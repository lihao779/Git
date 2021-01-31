#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <json/json.h>


#define TCP_PORT 17878
#define UDP_PORT 17878
#define CAPACITY 10
#define UDP_MAX_DATE 10240
#define UDPSEND_MAX 10

//////注册请求数据格式////////
struct RegisterInfo
{
    RegisterInfo()
    {
        memset(nick_name_,'\0',sizeof(nick_name_));
        memset(school_,'\0',sizeof(school_));
        memset(passwd_,'\0',sizeof(passwd_));
    }
    char nick_name_[20]; //昵称
    char school_[20]; // 学校
    char passwd_[20]; // 密码
};




//////登录请求数据格式////////
struct LoginInfo
{
    LoginInfo()
    {
        memset(&id_,'\0',sizeof(id_));
        memset(passwd_,'\0',sizeof(passwd_));

    }
    uint32_t id_;
    char passwd_[20];
};



//////服务端给客户端回复请求的数据格式///////
/*
 * 注册：注册状态&用户ID---类似"QQ"号
 * 登录：登录状态
 */
struct ReplyInfo
{
    int resp_status_;
    uint32_t id_;
};

enum Status
{
    REGISTER_FAILED = 0,
    REGISTER_SUCCESS,
    LOGIN_FAILED,
    LOGIN_SUCCESS,
    ONLINE
};

//////如何标识是注册请求还是登录请求/////////
enum Resq_type
{
    REGISTER_RESQ = 0,
    LOGIN_RESQ
};


//双方约定udp数据格式
class UdpMsg
{
    public:
        UdpMsg()
        {}
        ~UdpMsg()
        {}

        void serialize(std::string* msg);//序列化udp数据
        void deserialize(const std::string msg);//反序列化udp数据
        std::string& Get_nick_name();
        std::string& Get_school();
        uint32_t& Get_id();
        std::string& Get_msg();
    private:
        std::string nick_name_;
        std::string school_;
        uint32_t id_;
        std::string msg_;
};
void UdpMsg::serialize(std::string* msg)
{
    Json::Value json_val;
    json_val["nick_name"] = nick_name_;
    json_val["school"] = school_;
    json_val["msg"] = msg_;
    json_val["user_id"] = id_;

    Json::FastWriter writer;
    *msg = writer.write(json_val);
}
void UdpMsg::deserialize(const std::string msg)
{
    Json::Reader read;
    Json::Value val;
    read.parse(msg,val);
    nick_name_ = val["nick_name"].asString();
    school_ = val["school"].asString();
    msg_ = val["msg"].asString();
    id_ = val["user_id"].asUInt();
}
std::string& UdpMsg::Get_nick_name()
{
    return nick_name_;
}
std::string& UdpMsg::Get_school()
{
    return school_;
}
uint32_t& UdpMsg::Get_id()
{
    return id_;
}
std::string& UdpMsg::Get_msg()
{
    return msg_;
}
