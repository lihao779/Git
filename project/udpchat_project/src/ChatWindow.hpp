#pragma once
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <unordered_set>

#include <ncurses.h>
#include "ConnectInfo.hpp"
#include "ChatClient.hpp"
#include "tools.hpp"

class ChatWindow;
class Pram
{
    public:
        Pram(int thread_num,ChatWindow* cw,UdpClient* uc)
            :thread_num_(thread_num)
             ,cw_(cw)
             ,uc_(uc)
    {}
        ChatWindow* GetChatWindow_this();
        int GetThread_num();
        UdpClient* GetUdpClient();
    private:
        int thread_num_;
        ChatWindow* cw_;
        UdpClient* uc_; 
};
ChatWindow* Pram::GetChatWindow_this()
{
    return cw_;
}
int Pram::GetThread_num()
{
    return thread_num_;
}
UdpClient* Pram::GetUdpClient()
{
    return uc_;
}

class ChatWindow
{
    public:
        ChatWindow()
        {
            header_ = nullptr;
            output_ = nullptr;
            user_list_ = nullptr;
            input_ = nullptr;
            pthread_mutex_init(&window_lock_,nullptr);
            tid_.clear();
        }
        ~ChatWindow()
        {
            if(header_)
            {
                delwin(header_);
                header_ = nullptr;
            }
            if(output_)
            {
                delwin(output_);
                output_ = nullptr;
            }
            if(user_list_)
            {
                delwin(user_list_);
                user_list_ = nullptr;
            }
            if(input_)
            {
                delwin(input_);
                input_ = nullptr;
            }
            pthread_mutex_destroy(&window_lock_);
            endwin();
        }

        int Start(UdpClient* uc);
    
        static void* RunWindowStart(void* arg);
        void Wrefresh(WINDOW* win);
        void RunHeader();
        void Runoutput(UdpClient* uc);
        void RunInput(UdpClient* uc);
        void RunUser_list(UdpClient* uc);

    private:
        WINDOW* header_;
        WINDOW* output_;
        WINDOW* user_list_;
        WINDOW* input_;

        std::vector<pthread_t> tid_;
        pthread_mutex_t window_lock_;

};
int ChatWindow::Start(UdpClient* uc)
{
    initscr();
    for(int i = 0;i < 4;i++)
    {
        Pram* pram = new Pram(i,this,uc);
        pthread_t tid;
        int ret = pthread_create(&tid,NULL,RunWindowStart,pram);
        if(ret < 0)
        {
            return -1;
        }
        tid_.push_back(tid);
    }
    for(size_t i = 0;i < tid_.size();i++)
    {
        pthread_join(tid_[i],NULL);
    }
    return 0;
}
void* ChatWindow::RunWindowStart(void* arg)
{
    Pram* pram = (Pram*)arg;
    int thread_num = pram->GetThread_num();
    ChatWindow* cw = pram->GetChatWindow_this();
    delete pram;
    switch(thread_num)
    {
        case 0:
            //header_
            cw->RunHeader();
            break;
        case 1:
            //output_
            cw->Runoutput(pram->GetUdpClient());
            break;
        case 2:
            //user_list_
            cw->RunUser_list(pram->GetUdpClient());
            break;
        case 3:
            //input_
            cw->RunInput(pram->GetUdpClient());
            break;
    }
    return nullptr;
}
void ChatWindow::Wrefresh(WINDOW* win)
{
    pthread_mutex_lock(&window_lock_);
    wrefresh(win);
    pthread_mutex_unlock(&window_lock_);
}

void ChatWindow::RunHeader()
{
    WINDOW* oldheader = nullptr;
    while(1)
    {
        header_ = newwin(LINES/5,COLS,0,0);
        box(header_,0,0);
        Wrefresh(header_);


        if(oldheader)
        {
            delwin(oldheader);
            oldheader = nullptr;
        }
        std::string msg = "welcome our chatting";

        int x,y;
        getmaxyx(header_,y,x);
        mvwaddstr(header_,y/2,(x-msg.size()) / 2,msg.c_str());
        Wrefresh(header_);
        oldheader = header_;
        sleep(1);
    }
}
void ChatWindow::Runoutput(UdpClient* uc)
{
    output_ = newwin(LINES*3/5,COLS*3/4,LINES/5,0);
    box(output_,0,0);
    Wrefresh(output_);
    int x,y;
    getmaxyx(output_,y,x);

    int line = 1;
    while(1)
    {

        std::string msg;
        uc->RecvUdpMsg(&msg);
        UdpMsg um;                              
        um.deserialize(msg);
        std::string show_msg;   
        show_msg += um.Get_nick_name(); 
        show_msg += "-" ;
        show_msg += um.Get_school();
        show_msg += ":" ;
        show_msg += um.Get_msg();
        if(line == y - 1)
        {
            line = 1;   
            delwin(output_);
            output_ = nullptr;
            output_ = newwin(LINES*3/5,COLS*3/4,LINES/5,0);
            box(output_,0,0);
            Wrefresh(output_);

        }
        mvwaddstr(output_,line,1,show_msg.c_str());
        Wrefresh(output_);
        line++;

        std::unordered_map<uint32_t,UdpMsg>& online = uc->GetOnline();
        online.insert(std::make_pair(um.Get_id(),um));
    }
}
void ChatWindow::RunInput(UdpClient* uc)
{
    WINDOW* oldwin = nullptr;
    while(1)
    {
        input_ = newwin(LINES/5,COLS,LINES*4/5,0);
        box(input_,0,0);
        Wrefresh(input_);
        if(oldwin)
        {
            delwin(oldwin);
            oldwin = nullptr;
        }

        std::string tips = "please enter msg:";
        mvwaddstr(input_,1,1,tips.c_str());
        Wrefresh(input_);
        char buf[UDP_MAX_DATE] = {0};
        wgetnstr(input_,buf,sizeof(buf)-1);


        UdpMsg um;
        um.Get_nick_name() = uc->GetMe().nick_name_;
        um.Get_id() = uc->GetMe().user_id_;
        um.Get_school() = uc->GetMe().school_;
        um.Get_msg().assign(buf,strlen(buf));

        std::string send_msg;
        um.serialize(&send_msg);

        uc->SendUdpMsg(send_msg);
        oldwin = input_;
    }
}
void ChatWindow::RunUser_list(UdpClient* uc)
{
    while(1)
    {
        user_list_ = newwin(LINES*3/5,COLS/4,LINES/5,COLS*3/4);
        box(user_list_,0,0);
        Wrefresh(user_list_);
        int x,y;
        getmaxyx(user_list_,y,x);
        int line = 1;
        std::unordered_map<uint32_t,UdpMsg>& online = uc->GetOnline();
    
        auto it = online.begin();
        while(it != online.end())
        {
            std::string msg = it->second.Get_nick_name();
            msg += ":";
            msg += it->second.Get_school();
            if(line == y - 1)
            {
                delwin(user_list_);
                user_list_ = newwin(LINES*3/5,COLS/4,LINES/5,COLS*3/4);
                box(user_list_,0,0);
                Wrefresh(user_list_);
                line = 1;
            }
            mvwaddstr(user_list_,line,1,msg.c_str());
            Wrefresh(user_list_);
            line++;
            it++;
        }
        sleep(3);
    }
}
