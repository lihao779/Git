#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("./fifo",O_RDWR);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }
    char buf[1024] = "i love you";
    write(fd,buf,strlen(buf));
    while(1)
    {
        sleep(1);
    }
    close(fd);

    return 0;
}
