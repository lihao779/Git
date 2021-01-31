#include <unistd.h>
#include "ChatClient.hpp"

void Meun()
{
    std::cout << "*********************************" << std::endl;
    std::cout << "******1.register *** 2.login*****" << std::endl;
    std::cout << "******3.logout   *** 4.exit *****" << std::endl;
    std::cout << "*********************************" << std::endl;
}


int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        std::cout << "using ./ChatClient -ip [ip]" << std::endl;
        return -1;
    }
    
    std::string ip;
    for(int i = 0; i < argc;i++)
    {
        if(strcmp(argv[i],"-ip") == 0 && i+1 < argc)
        {
            ip = argv[i+1];
        }
        
    }
    if(ip.size() == 0)
    {
        LOG(ERROR,"Illegal IP,please retry start ChatClient") << std::endl;
        return -1;
    }
    
    UdpClient uc;
    while(1)
    {
        Meun();
        std::cout <<"please enter your select:";
        fflush(stdout);
        int select = -1;
        std::cin >> select;
        if(select == 1)
        {
            //注册逻辑
            int ret = uc.RegistertoSvr(ip);
            if(ret < 0)
            {
                LOG(WARNING,"please retry register") << std::endl;
            }
            else if(ret == 0)
            {
                LOG(INFO,"register success ,please login") <<std::endl;
            }
            uc.CloseFd();
        }
        else if(select == 2)
        {
            //登录逻辑
           int ret = uc.LogtoSvr(ip); 
           if(ret < 0)
           {
               LOG(ERROR,"please retry login") << std::endl;
           }
           else
           {
               LOG(INFO,"login success ,please chatting") <<std::endl;
               uc.CreateUdpSock();
               while(1)
               {
                    std::string msg;
                    std::cout << "please enter your msg:";
                    std::cin >> msg;
                    uc.SendUdpMsg(msg,ip);     
                    uc.RecvUdpMsg();
               }
           }
           uc.CloseFd();
        }
        else if(select == 3)
        {
            //登出
        }
        else if(select == 4)
        {
            //退出
            LOG(INFO,"eixt chat cliect") << std::endl;
            exit(0);
        }
        else
        {
            //输入错误
        }
    }


    while(1)
    {
        sleep(1);
    }
    return 0;
}
