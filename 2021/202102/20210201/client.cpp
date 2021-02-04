#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
int sockfd;

void hander(int sig)
{
    char buf[4] = {0};
    recv(sockfd,buf,sizeof(buf) - 1,0);
    std::cout <<"hander" <<std::endl;
    std::cout << buf << std::endl;
}
int main()
{
    signal(SIGIO,hander);
    sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    
    fcntl(sockfd,F_SETOWN,getpid());
    int flag = fcntl(sockfd,F_GETFL,0);
    flag |= O_NONBLOCK;
    flag |= O_ASYNC;
    fcntl(sockfd,F_SETFL,flag);

    connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    while(1)
    {
        sleep(1);
    }
    return 0;
}
