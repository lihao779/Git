#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
int main()
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
     struct sockaddr_in addr;
     addr.sin_family = AF_INET;
     addr.sin_port = htons(19999);                                              
     addr.sin_addr.s_addr = inet_addr("192.168.40.131");
     int bind_return = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
     if(bind_return < 0)
     {
         perror("bind");
         return -1;
     }
    
    struct sockaddr_in svr;
    svr.sin_family = AF_INET;
    svr.sin_port = htons(19999);
    svr.sin_addr.s_addr = inet_addr("192.168.40.131");
    while(1)
    {
        
        char buf[1024] = {0};
        printf("cil:"); 
        fflush(stdout);
        std::cin>>buf;
        int ret =  sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&svr,sizeof(svr));
        if(ret < 0)
        {
            perror("sendto");
            return -1;
        }
        memset(buf,0,sizeof(buf));
        recvfrom(sockfd,buf,sizeof(buf)-1,0,NULL,NULL);
        printf("svr:%s\n",buf);

    }
    close(sockfd);
    return 0;
}
