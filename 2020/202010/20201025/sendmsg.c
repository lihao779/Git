#include<sys/types.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>
#define PATH_NAME    "."
#define PROJ_ID       1//100
#define BUF_SIZE      1024 

int main()
{
	int qid;//消息队列标识符
	key_t msgkey;
	int len ;
	struct mymsgbuf
	{
		long msgtype;
		char buf[BUF_SIZE];
	}msgbuffer;


	//获取键值
	if((msgkey = ftok(PATH_NAME,PROJ_ID)) < 0)
	{
		perror("ftok");
		exit(1);
	}
	//获取消息队列标识符
	if((qid = msgget(msgkey,IPC_CREAT|0660))<0)
	{
		perror("msgget");
		exit(1);
	}
	msgbuffer.msgtype = 3;
	strcpy(msgbuffer.buf,"i am message");
	len = sizeof(msgbuffer)-4;

	if(msgsnd(qid,&msgbuffer,len,0)<0)
	{
		perror("msgsnd");
		exit(1);
	}


	return 0;
}
