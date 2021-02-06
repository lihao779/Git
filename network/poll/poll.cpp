#include <poll.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
    struct pollfd array[10];
    array[0].fd = 0;
    array[0].events = POLLIN;
    array[0].fd = 1;
    array[0].events = POLLIN;

    int ret = poll(array,2,-1);
    if(ret < 0)
    {
        perror("poll");
        return -1;
    }
    for(int i = 0;i < 10;i++)
    {
    if(array[i].revents == POLLIN)
    {
        char buf[1024] = {0};
        read(0,buf,sizeof(buf)-1);
        printf("buf is %s\n",buf);
    }
    }
    return 0;
}
