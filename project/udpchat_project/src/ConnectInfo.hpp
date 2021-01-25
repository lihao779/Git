#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>

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
    LOGIN_SUCCESS
};

//////如何标识是注册请求还是登录请求/////////
enum Resq_type
{
    REGISTER_RESQ = 0,
    LOGIN_RESQ
};
