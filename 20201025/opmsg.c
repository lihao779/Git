#include<time.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_SIZE 1024
#define PATH_NAME "."
#define PROJ_ID   1
void getmsgattr(int id_msg,struct msqid_ds* ptr);
int main()
{
    struct msgbuf
    {
        long msgtype;
        char buf[BUF_SIZE];
    }mymsgbuf;
    
    struct msqid_ds msg_attr;
    key_t key_msg;
    int id_msg;
    if((key_msg = ftok(PATH_NAME,PROJ_ID))<0)
    {
        perror("ftok");
        exit(1);
    }
    //设置消息队列
    if((id_msg = msgget(key_msg,IPC_CREAT|0664))<0)
    {
        perror("msgget");
        exit(1);
    }
    //查看属性
    getmsgattr(id_msg,&msg_attr);
    //添加消息
    mymsgbuf.msgtype = 3;
    strcpy(mymsgbuf.buf,"linux");
    int len = sizeof(mymsgbuf)-4;
    msgsnd(id_msg,&mymsgbuf,len,0);
    //查看属性
    getmsgattr(id_msg,&msg_attr);
    //修改属性
    msg_attr.msg_perm.uid = 3;
    msg_attr.msg_perm.gid = 2;
    msg_attr.msg_perm.mode = 0666;
    if(msgctl(id_msg,IPC_SET,&msg_attr)<0)
    {
        perror("msgctl");
        exit(1);
    }
    //查看属性
    getmsgattr(id_msg,&msg_attr);
    //删除消息队列
    if(msgctl(id_msg,IPC_RMID,NULL)<0)
    {
        perror("msgctl");
        exit(1);
    }
    //查看属性
    getmsgattr(id_msg,&msg_attr);
    return 0;
    
}
void getmsgattr(int id_msg,struct msqid_ds* ptr)
{
    printf("**************msgattr********************begin**************\n");
    if(msgctl(id_msg,IPC_STAT,ptr)<0)
    {
        perror("msgctl");
        return;
    }
    printf("this is %d message\n",id_msg);
    printf("msg uid is %d\n",ptr->msg_perm.uid);
    printf("msg gid is %d\n",ptr->msg_perm.gid);
    printf("msg mode is %d\n",ptr->msg_perm.mode);
    printf("last msgrv to msq time is %s\n",ctime(&(ptr->msg_stime)));
    printf("last change msq time is %s\n",ctime(&(ptr->msg_ctime)));



    printf("**************mesgarrt*******************end****************\n");
}






