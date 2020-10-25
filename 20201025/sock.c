#include<sys/socket.h>
#include<stdio.h>

int main()
{
    //int sock_fd = socket(AF_INET,SOCK_STREAM,0);
    int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
    if(sock_fd<0)
    {
        perror("socker");
        return 1;
    }
    printf("sock_fd = %d\n",sock_fd);
    return 0;
}
