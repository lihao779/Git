#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
char* sock_ntop(const struct sockaddr* sockaddr, socklen_t addrlen)
{
    char port[16];
    static char result[128];
    if(sockaddr->sa_family == AF_INET)
    {
        struct sockaddr_in* addr = (struct sockaddr_in*)sockaddr;
        if(inet_ntop(AF_INET, &addr->sin_addr, result, sizeof(result)) == nullptr) 
        {
            return nullptr;
        }
        if(ntohs(addr->sin_port) != 0)
        {
            snprintf(port, sizeof(port), ":%d", ntohs(addr->sin_port));
        }
        strncat(result, port, sizeof(port));
        return result;
    }
    return nullptr;

}
