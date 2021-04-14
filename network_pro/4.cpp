#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
int main()
{
    struct sockaddr_in sevaddr, cliaddr;
    int listenfd, connfd;
    socklen_t len;
    char buf[1024];
    time_t tick;
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenfd < 0)
    {
        return -1;
    }
    sevaddr.sin_family = AF_INET;
    sevaddr.sin_port = htons(9000);
    sevaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(listenfd, (struct sockaddr*)&sevaddr, sizeof(sevaddr));
    if(ret < 0)
    {
        close(listenfd);
        return -1;
    }
    ret = listen(listenfd, 5);
    if(ret < 0)
    {
        close(listenfd);
        return -1;
    }

    while(1)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
        if(connfd < 0)
        {
            close(listenfd);
            return -1;
        }
        printf("connect ip:%s,port:%d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)), ntohs(cliaddr.sin_port));
        
        tick = time(NULL);
        snprintf(buf, sizeof(buf) - 1, "%s", ctime(&tick));

        write(connfd, buf, strlen(buf));
        close(connfd);

    }

    return 0;
}
