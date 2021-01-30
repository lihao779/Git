#pragma once

#include <iostream>
#include <string>
#include <queue>

#include "ConnectInfo.hpp"

class MsgPool
{
    public:
        MsgPool(int capacity = CAPACITY)
        {
           capacity_ = capacity;
           pthread_mutex_init(&msg_lock_,NULL);
           pthread_cond_init(&con_cond_,NULL);
           pthread_cond_init(&pro_cond_,NULL);
        }
        ~MsgPool()
        {
            pthread_cond_destroy(&con_cond_);
            pthread_cond_destroy(&pro_cond_);
            pthread_mutex_unlock(&msg_lock_);
        }
        void PushMsg(const std::string& s);
        void PopMsg(std::string* s);
    private:
    std::queue<std::string> msg_;
    size_t capacity_;
    pthread_mutex_t msg_lock_;
    pthread_cond_t con_cond_;
    pthread_cond_t pro_cond_;
};


void MsgPool::PushMsg(const std::string& s)
{
    pthread_mutex_lock(&msg_lock_);
    while(msg_.size() == capacity_)
    {
        pthread_cond_wait(&pro_cond_,&msg_lock_);
    }
    msg_.push(s);
    pthread_mutex_unlock(&msg_lock_);
    pthread_cond_signal(&con_cond_);
}
void MsgPool::PopMsg(std::string* s)
{
    pthread_mutex_lock(&msg_lock_);
    while(msg_.size() == 0)
    {
        pthread_cond_wait(&con_cond_,&msg_lock_);
    }
    *s = msg_.front();
    msg_.pop();
    pthread_mutex_unlock(&msg_lock_);
    pthread_cond_signal(&pro_cond_);
}
