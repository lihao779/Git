#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#define PORT 9000
#define LISTEN 5

void str_echo(int);
void handler(int);
int main()
{
    signal(SIGCHLD, handler);
    int listenfd, connfd;
    struct sockaddr_in svraddr, childaddr;
    socklen_t len;
    
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenfd < 0)
    {
        perror("socket error");
        exit(0);
    }

    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(PORT);
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(listenfd, (struct sockaddr*)&svraddr, sizeof(svraddr));
    if(ret < 0)
    {
        perror("bind error");
        close(listenfd);
        exit(0);
    }

    ret = listen(listenfd, LISTEN);
    if(ret < 0)
    {
        perror("listen error");
        close(listenfd);
        exit(0);
    }

    while(1)
    {
        len = sizeof(childaddr);
        connfd = accept(listenfd, (struct sockaddr*)&childaddr, &len);
        if(connfd < 0)
        {
            if(errno == EINTR)
                continue;
            else
            {
                perror("accept error");
                continue;
            }
        }
        if(fork() == 0)
        {
            close(listenfd);
            str_echo(connfd);

            close(connfd);
            exit(0);
        }
        close(connfd);
    }
    return 0;
}


void handler(int)
{
    /*
    int status;
    pid_t pid;
    pid = wait(&status);
    printf("child %d terminated\n", pid);
    return;
    */

    pid_t pid = 0;
    int status;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    return;
}

#define BUFSIZE 1024
void str_echo(int connfd)
{
    int n = 0;
    char buf[BUFSIZE] = {0};
    int left, right;
    while((n = read(connfd, buf, sizeof(buf) - 1)) > 0)
    {
        if(sscanf(buf, "%d %d",&left, &right) == 2)
        {
            memset(buf, '\0', sizeof(buf));
            snprintf(buf, sizeof(buf) - 1, "%d\n", left + right);
        }
        else
        {
            memset(buf, '\0', sizeof(buf));
            snprintf(buf, sizeof(buf) - 1, "input error\n");
        }
        write(connfd, buf, n);
    }
    if(n < 0)
    {
        perror("read error");
        return;
    }

}
