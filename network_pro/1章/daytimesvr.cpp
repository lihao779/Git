#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main()
{
    struct sockaddr_in addr, cliaddr;
    int listenfd, sockfd;
    socklen_t len;
    time_t ticks;
    char buf[1024];
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr)) ;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 接收任意网卡

    bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));

    listen(listenfd, 5);

    for(; ; )
    {
	    len = sizeof(cliaddr);
        sockfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
	    printf("connect ip:%s, port:%d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)), ntohs(cliaddr.sin_port));
        time(&ticks);        
        snprintf(buf, sizeof(buf) - 1, "%s\r\n", ctime(&ticks));
        write(sockfd, buf, strlen(buf));
        close(sockfd);
    }
    return 0;
}
