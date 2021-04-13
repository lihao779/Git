#include <iostream>
#include <string>

#include "cliect.hpp"



void Meun()
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "------1.注册        2.登录-------" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "---------------------------------" << std::endl;
}
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "please input ./cli [ip] [port]" << std::endl;
    }
    std::string ip = argv[1];
    uint32_t port = atoi(argv[2]);
    Cli client(ip, port);
    int ret = client.Conn();
    if(!ret)
        std::cout << "conn server failed" << std::endl;
    while(1)
    {
        Meun();
        int select = -1;
        std::cout << "please input your select:";
        std::cin >> select;
        switch(select)
        {
            case 1:
                client.Register();
                break;
            case 2:
                client.Login();
                break;
            default:
                {
                    std::cout << "输入错误，请重新输入" << std::endl;
                    continue;
                }
                break;
        }
    }
    return 0;
}
