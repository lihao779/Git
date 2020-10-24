#include <stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<stdlib.h>
#include <sys/msg.h>

#define PATH_NAME  "."
#define PROJ_ID    1
#define BUF_SIZE   1024


int main()
{
    struct msgbuf
    {
        long msgtype;
        char buf[BUF_SIZE];
    }mymsgbuf;

    key_t msgkey;
    int msgid;
    int len ;

    if((msgkey = ftok("PATH_NAME",PROJ_ID))<0)
    {
        perror("ftok");
        exit(1);
    }
    if((msgid = msgget(msgkey,IPC_CREAT|0664))<0)
    {
        perror("msgget");
        exit(1);
    }
    len = sizeof(mymsgbuf)-4;
    if(msgrcv)
    return 0;
}

