#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <string>

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        printf("using : ./a.out [ip] [port]\n");
        return -1;
    }
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    int listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listenfd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    int ret = bind(listenfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        close(listenfd);
        return -1;
    }
    ret = listen(listenfd,5);
    if(ret < 0)
    {
        perror("listen");
        close(listenfd);
        return -1;
    }
    int sockfd = accept(listenfd,NULL,NULL);
    if(sockfd < 0)
    {
        perror("accept");
        close(listenfd);
        return -1;
    }

    while(1)
    {
        char buf[1024] = {0};
        ssize_t recv_size = recv(sockfd,buf,sizeof(buf) - 1,0);
        if(recv_size < 0)
        {
            perror("recv");
            close(sockfd);
            close(listenfd);
            return -1;
        }
        else if(recv_size == 0)
        {
            printf("chrome shundown\n");
            close(sockfd);
            close(listenfd);
            return -1;
        }
        printf("chrome say:%s\n",buf);

        std::string body = "<html>hello bite 84</html>";
        //模拟http协议
        // memset(buf,'\0',sizeof(buf));
        // snprintf(buf,sizeof(buf) - 1,"%s %s %s\r\nContent-Type: text/html\r\nContent-Length: %zu\r\n\r\n","HTTP/1.1","200","OK",body.size());
        //buf==>响应报头
        //body==>响应正文
        // send(sockfd,buf,strlen(buf),0);
        // send(sockfd,body.c_str(),body.size(),0);
        // 302
        //std::stringstream ss;
        //ss << "HTTP/1.1 302 Redirect\r\n" ;
        //ss << "Content-Type: text/html\r\n";
        //ss << "Content-Length: " << body.size() <<"\r\n";
        //ss << "Location: https://www.baidu.com\r\n";
        //ss << "\r\n";
        //send(sockfd,ss.str().c_str(),ss.str().size(),0);
        //send(sockfd,body.c_str(),body.size(),0);
        //404
        std::stringstream ss;
        ss << "HTTP/1.1 404 page not found\r\n" ;
        ss << "Content-Type: text/html\r\n";
        ss << "Content-Length: " << body.size() <<"\r\n";
        ss << "\r\n";
        send(sockfd,ss.str().c_str(),ss.str().size(),0);
        send(sockfd,body.c_str(),body.size(),0);
        

    }
    close(sockfd);
    close(listenfd);
    return 0;
}
