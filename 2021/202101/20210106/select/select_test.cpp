#include <stdio.h>
#include <unistd.h>

#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    listen(sockfd,5);


    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0,&readfds);
    FD_SET(sockfd,&readfds);

    while(1)
    {
    fd_set temp = readfds;
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    // int ret = select(sockfd+1,&readfds,NULL,NULL,NULL);
    int ret = select(sockfd+1,&temp,NULL,NULL,&tv);
    if(ret < 0)
    {
        perror("select");
        return -1;
    }
    else if(ret == 0)
    {
        ret = FD_ISSET(0,&temp);
        printf("0 ret = %d\n",ret);

        ret = FD_ISSET(sockfd,&temp);
        printf("sockfd ret = %d\n",ret);
    }
    else
    {
        if(FD_ISSET(0,&temp))
        {
          char buf[1024] = {0};
          read(0,buf,sizeof(buf) - 1); 
          printf("buf:%s",buf);

        }
        if(!FD_ISSET(sockfd,&temp))
        {
            printf("sockfd is not in temp\n");
        }
        else
        {
            printf("sockfd is in temp\n");
        }
    }
    }
    
    return 0;
}
