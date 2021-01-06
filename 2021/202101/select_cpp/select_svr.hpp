#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

class SelectSvr
{
    public:
        SelectSvr()
        {
            maxfd_ = -1;
            FD_ZERO(&readfds);
        }
        ~SelectSvr(){}

        //监控接口
        int Select();//select
        void AddFd(int fd);
        void DeleteFd(int fd);
        void JudgeFd();


    private:
        // 最大文件描述符
        int maxfd_;
        // 可读事件集合
        fd_set readfds;
};
void SelectSvr::AddFd(int fd)
{
    FD_SET(fd,&readfds);
    if(fd > maxfd_)
        maxfd_ = fd;
}
void SelectSvr::DeleteFd(int fd)
{
    if(FD_ISSET(fd,&readfds))
    {
        FD_CLR(fd,&readfds);
        for(int i = maxfd_; i>=0;--i)
        {
            if(FD_ISSET(i,&readfds))
            {
                maxfd_ = i;
                return ;
            }
        }
        maxfd_ = -1;
    }
    
}
