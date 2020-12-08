#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <sstream>

int main()
{
    int listen_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_sock < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19998);
    addr.sin_addr.s_addr = inet_addr("192.168.40.131");

    int ret = bind(listen_sock,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        close(listen_sock);
        return -1;
    }
    ret = listen(listen_sock,1);
    if(ret < 0)
    {
        perror("listen");
        close(listen_sock);
        return -1;
    }
    int sockfd = accept(listen_sock,NULL,NULL);
    if(sockfd < 0)
    {
        perror("accept");
        close(listen_sock);
        return -1;
    }
    while(1)
    { 
        /*
        char buf[1024] = {0};
        ret = recv(sockfd,buf,sizeof(buf)-1,0);
        if(ret < 0)
        {
            perror("recv");
            close(sockfd);
            close(listen_sock);
            return -1;
        }
        else if(ret == 0)
        {
            printf("cil sockfd shundown\n");
            close(sockfd);
            close(listen_sock);
            return 0;
        }
        printf("cli:%s",buf);
        */


        //<html>hello bite 84</html>
        //首行首行
        //响应报头
        //空行
        //响应体
        std::string body = "<html>hello bite 84</html>";
        std::stringstream ss;
        ss << "HTTP/1.1 200 OK\r\n";
        ss << "Content-Type: text/html\r\n";
        ss << "Content-Length: "<<body.size()<<"\r\n";
        ss << "\r\n";
        ret = send(sockfd,ss.str().c_str(),ss.str().size(),0);
    //    if(ret < 0)
    //    {
    //        perror("send");
    //        close(sockfd);
    //        close(listen_sock);
    //        return -1;
    //    }
        ret = send(sockfd,body.c_str(),body.size(),0);
    //    if(ret < 0)
    //    {
    //        perror("send");
    //        close(sockfd);
    //        close(listen_sock);
    //        return -1;
    //    }
         ss.clear();
         ss.str() = "";
    }
    close(sockfd);
    close(listen_sock);
    return 0;
}

