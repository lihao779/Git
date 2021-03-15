#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <iostream>

using namespace std;

int main()
{
    int epoll_fd = epoll_create(10);
    if(epoll_fd < 0)
    {
        cout << "create failed" << endl;
        return -1;
    }
    int flag = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, flag | O_NONBLOCK);
    struct epoll_event ee;
    ee.events = EPOLLIN | EPOLLET;
    ee.data.fd = 0;
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD, 0, &ee);
    
    while(1)
    {
        struct epoll_event fd_arr[1];
        int ret = epoll_wait(epoll_fd, fd_arr, sizeof(fd_arr)/sizeof(fd_arr[0]), -1);
        if(ret < 0)
        {
            continue;
        }

        for(size_t i = 0; i < sizeof(fd_arr)/sizeof(fd_arr[0]); i++)
        {
            if(fd_arr[i].data.fd == 0)
            {
                string s;
                while(1)
                {
                    char buf[3] = {0};
                    int ret = read(0, buf, sizeof(buf) - 1);
                    if(ret < 0)
                    {
                        if(errno == EAGAIN || errno == EWOULDBLOCK)
                        {
                            cout << "正常情况" << endl;
                        }
                        break;
                    }
                    else if(ret < sizeof(buf) - 1)
                    {
                        s.append(buf, strlen(buf));
                        break;
                    }
                    s.append(buf, strlen(buf));
                }
                cout << s << endl;
            }
        }
    }
    return 0;
}
