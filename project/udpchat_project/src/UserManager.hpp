#pragma once
#include <pthread.h>
#include <string>
#include <unordered_map>


#include "ConnectInfo.hpp"

/*
 * key-value维护在线数据信息
 * key：用户id
 * vaule：单个用户信息
 * 
 */


class UserInfo
{
    public:
        UserInfo(std::string nick_name,std::string school,std::string passwd,uint32_t userid)
            :nick_name_(nick_name)
             ,school_(school)
             ,passwd_(passwd)
             ,userid_(userid)
             ,user_status(REGISTER_FAILED)
        {}
        ~UserInfo()
        {}
        const std::string GetPasswd();
        void SetUserStatus(int status);

    private:
        std::string nick_name_;
        std::string school_;
        std::string passwd_;

        uint32_t userid_;//用户id
        int user_status;
};
const std::string UserInfo::GetPasswd()
{
    return passwd_;
}
void UserInfo::SetUserStatus(int status)
{
    user_status = status;
}


class UserManage
{
    public:
        UserManage()
        {
            pthread_mutex_init(&map_lock_,NULL);
            user_map_.clear();
            prepare_id_ = 0;
        }
        ~UserManage()
        {
            pthread_mutex_destroy(&map_lock_);
        }

        int DealRegister(const std::string& nick_name,const std::string& school,const std::string passwd,uint32_t* user_id);
        int DealLogin(uint32_t id,const std::string& passwd);
    private:
        std::unordered_map<uint32_t,UserInfo> user_map_;//key-value(id-usermessage)
        pthread_mutex_t map_lock_;// 保护user_map的线程安全
        uint32_t prepare_id_; //预分配id
};

int UserManage::DealRegister(const std::string& nick_name,const std::string& school,const std::string passwd,uint32_t* user_id)
{
    if(nick_name.size() == 0 || school.size() == 0 || passwd.size() == 0)
        return -1;
    pthread_mutex_lock(&map_lock_);

    UserInfo ui(nick_name,school,passwd,prepare_id_);
    ui.SetUserStatus(REGISTER_SUCCESS);
    user_map_.insert(std::make_pair(prepare_id_,ui));
    *user_id = prepare_id_;
    prepare_id_++;

    pthread_mutex_unlock(&map_lock_);
    return 0;
}
int UserManage::DealLogin(uint32_t id,const std::string& passwd)
{
    if(passwd.size() == 0)
        return -1;
    std::unordered_map<uint32_t,UserInfo>::iterator iter;
    pthread_mutex_lock(&map_lock_);
    iter = user_map_.find(id);
    if(iter == user_map_.end())
    {
        pthread_mutex_unlock(&map_lock_);
        return -2;
    }
    const std::string reg_passwd = iter->second.GetPasswd();
    if(reg_passwd != passwd)
    {
    iter->second.SetUserStatus(LOGIN_FAILED);
        pthread_mutex_unlock(&map_lock_);
        return -3;
    }
    iter->second.SetUserStatus(LOGIN_SUCCESS);
    pthread_mutex_unlock(&map_lock_);
    return 0;
}
