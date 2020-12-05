#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int fd = open("fifo",O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return -1 ;
    }
    char buf[1024] = {0};
    read(fd,buf,sizeof(buf)-1);
    printf("%s\n",buf);
    while(1)
    {
        sleep(1);
    }

    return 0;
}
