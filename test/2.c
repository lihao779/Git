#include <stdio.h>
#include <unistd.h>
#include <signal.h>


//void handler(int)
//{
//    printf("SIG_PIPE\n");
//    return ;
//}

int main()
{
//    signal(SIGPIPE, handler);
    int fd[2];
    int ret = pipe(fd);
    pid_t pid;
    if(ret < 0)
    {
        printf("pipe failed\n");
        return 0;
    }
    pid = fork();
    if(pid == 0)
    {
        //从管道读取
        close(fd[1]);
        close(fd[0]);
        while(1)
        {
            //char buf;
            //read(fd[0], &buf, 1);
            //printf("buf = %c\n", buf);
            sleep(1);
            printf("i am thread\n");
        }
    }
    else if(pid > 0)
    {
        //网管到写
        close(fd[0]);
        char buf = '1';
        while(1)
        {
            write(fd[1], &buf, 1);
            printf("i am main\n");
            sleep(1);
        }
    }
    else
    {
        printf("create fork failed\n");
        return 0;
    }

    return 0;
}
