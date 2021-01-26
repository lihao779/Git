#include <unistd.h>
#include "ChatClient.hpp"

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
    uc.RegistertoSvr(ip); 

    while(1)
    {
        sleep(1);
    }
    return 0;
}
