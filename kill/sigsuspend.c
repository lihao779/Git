#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void handler(int signo)
{
	printf("this is handler\n");
}

void my_err(char* err_string,int line)
{
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}
int main()
{

	//设置信号屏蔽函数
	if(SIG_ERR == signal(SIGINT,handler))
	{
		my_err("signal",__LINE__);
	}
	sleep(3);
	//屏蔽信号
	sigset_t newmask,oldmask,zeromask;

	sigemptyset(&newmask);
	sigemptyset(&zeromask);
	sigaddset(&newmask,SIGINT);

	if(-1 == sigprocmask(SIG_BLOCK,&newmask,&oldmask))
	{
		my_err("sigprocmask",__LINE__);
	}
	else
	{
		printf("SIGINT blocked\n");
	}
	sleep(2);
	//取消对所有信号的屏蔽并等待信号
	if(-1 != sigsuspend(&zeromask))
	{
		my_err("sigsuspend",__LINE__);
	}
	else
	{
		printf("success\n");
	}
	//恢复
	if(-1 == sigprocmask(SIG_SETMASK,&oldmask,NULL))
	{
		my_err("sigpromask",__LINE__);
	}
	while(1)
	{
		sleep(1);
	}
	return 0;
}
