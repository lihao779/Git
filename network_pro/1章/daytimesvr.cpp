#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main()
{
    struct sockaddr_in addr;
    int listenfd, sockfd;
    time_t ticks;
    char buf[1024];
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr)) ;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1300);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 接收任意网卡

    bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));

    listen(listenfd, 5);

    for(; ; )
    {
        sockfd = accept(listenfd, NULL, NULL);
        time(&ticks);        
        snprintf(buf, sizeof(buf) - 1, "%s\r\n", ctime(&ticks));
        write(sockfd, buf, strlen(buf));
        close(sockfd);
    }
    return 0;
}
