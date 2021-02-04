//运用select监控监听套接字和连接套接字
//创建tcp套接字
//创建readfds事件集合
//添加监听套接字到事件集合
//判断是否有接受信息
//将接收到的消息添加进reads事件集合
//继续监听


#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main()
{
    int sock_listen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock_listen < 0)
    {
        perror("sock_listen");
        exit(-1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(sock_listen,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        exit(-1);
    }
    ret = listen(sock_listen,5);
    if(ret < 0)
    {
        perror("listen");
        exit(-1);
    }
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock_listen,&readfds);
    int maxfd = sock_listen;
    while(1)
    {
        fd_set temp = readfds;
        ret = select(maxfd + 1,&temp,NULL,NULL,NULL);
        if(ret < 0)
        {
            perror("select");
            exit(-1);
        }
        else if(ret == 0)
        {
            //超时时间；
        }
        else
        {
            for(int i = 0;i <= maxfd;i++)
            {
                if(FD_ISSET(i,&temp))
                {
                   if(i == sock_listen) 
                   {
                        struct sockaddr_in addr;
                        socklen_t addrlen = sizeof(addr);
                        int newfd = accept(sock_listen,(struct sockaddr*)&addr,&addrlen);
                        if(newfd < 0)
                        {
                            perror("accept");
                            continue;
                        }
                        FD_SET(newfd,&readfds);
                        if(newfd > maxfd)
                            maxfd = newfd;
                        printf("ip is %s,port is %d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
                   }
                   else
                   {
                       char buf[1024] = {0};
                       ret = recv(i,&buf,sizeof(buf) - 1 ,0);
                       if(ret < 0)
                       {
                           perror("recv");
                           continue;
                       }
                       else if(ret == 0)
                       {
                           FD_CLR(i,&readfds);
                           int j = maxfd;
                           for(;j >= 0;j--)
                           {
                               if(FD_ISSET(j,&readfds))
                               {
                                   maxfd = j;
                                   break;
                               }
                           }
                           if(j < 0)
                           {
                            maxfd = -1; 
                           }
                       }
                       else
                        printf("%d fd recvmsg:%s\n",i,buf);
                   }
                }
            }
        }

    }
    return 0;

}

