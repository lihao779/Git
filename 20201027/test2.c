#include<stdio.h>
#include<sys/select.h>
#include<sys/types.h>
#include<time.h>

void dis_time(const char* string)
{
    int second;
    second = time(NULL);
    printf("%s:%d\n",string,second);
}


int main()
{
    fd_set readfds;
    struct timeval time;
    int ret; 
    FD_ZERO(&readfds);
    FD_SET(0,&readfds);

    while(1)
    {
    time.tv_sec = 10;
    time.tv_usec = 0;
    dis_time("before");
    ret = select(1,&readfds,NULL,NULL,&time);
    dis_time("end");
        switch(ret)
        {
            case 0:
                printf("no date input\n");
                break;
            case -1:
                printf("failed\n");
            default:
                getchar();
                printf("date is avaible\n");


        }

    }
}
