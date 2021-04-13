#include <string.h>
#include <arpa/inet.h>
#include <iostream>

int main()
{
    struct sockaddr_in addr;
    const char* ip = "192.168.0.1";

    if(inet_aton(ip, &addr.sin_addr))
    {
        std::cout << "转换成功" << std::endl;
    }
    else
    {
        std::cout << "转换失败" << std::endl;
    }

    auto ret = inet_addr("255.255.255.255");
    std::cout << "ret = " << ret << std::endl;
    
    std::cout << inet_ntoa(addr.sin_addr) << std::endl;
    bzero(&addr, sizeof(addr));

    if(inet_pton(AF_INET, ip, &addr.sin_addr))
    {
        std::cout << "转换成功" << std::endl;
    }
    else
    {
        std::cout << "转换失败" << std::endl;
    }

    char buf[17];
    std::cout << inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof(buf)) << std::endl;
    return 0;
}
