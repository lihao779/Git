#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <iostream>


int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    listen(sockfd, 5);

    //创建epoll句柄
    int epoll_fd = epoll_create(10);    
    if(epoll_fd < 0)
    {
        std::cout << "epoll 句柄创建失败" << std::endl;
        return -1;
    }
    struct epoll_event ee;
    ee.events = EPOLLIN;
    ee.data.fd = sockfd;
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,sockfd,&ee);

    while(1)
    {
        struct epoll_event fd_arr[10];
        int size = epoll_wait(epoll_fd, fd_arr, sizeof(fd_arr)/sizeof(fd_arr[0]), -1);
        if(size < 0)
        {
            continue;
        }
        for(size_t i = 0; i < sizeof(fd_arr)/sizeof(fd_arr[0]); i++)
        {
            //侦听套接字有内容
            if(fd_arr[i].data.fd == sockfd)
            {
                //accept
                sockaddr_in peeraddr;
                socklen_t peerlen = sizeof(peeraddr);
                int newfd = accept(sockfd,(struct sockaddr*)&peeraddr,&peerlen);
                if(newfd < 0)
                {
                    continue;
                }
                std::cout << "ip:port-->" << inet_ntoa(peeraddr.sin_addr) << " " << ntohs(peeraddr.sin_port) << std::endl;
                struct epoll_event ee;
                ee.events = EPOLLIN;
                ee.data.fd = newfd;
                epoll_ctl(epoll_fd,EPOLL_CTL_ADD,newfd,&ee);
            }
            else
            {
                char buf[1024] = {0};
                //recv
                int size = recv(fd_arr[i].data.fd, buf, sizeof(buf) - 1, 0);
                if(size < 0)
                {
                    continue;
                }
                else if(size == 0)
                {
                    //peer shutdown
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd_arr[i].data.fd, NULL);
                    close(fd_arr[i].data.fd);
                    continue;
                }
                else
                    std::cout << "recv:" << buf << std::endl;
            }
        }

    }
    return 0;
}
