#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>


int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    listen(sockfd,5);
    
    int peerfd = accept(sockfd,NULL,NULL);
    char buf[4] = "123";
    ssize_t ret = send(peerfd,buf,3,0);
    if(ret > 0)
    {
        std::cout << "发送成功" <<std::endl;
    }
    while(1)
    {
        sleep(1);
    }
    
    return 0;
}
