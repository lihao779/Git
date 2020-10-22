#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void my_err(char* err_string,int line)
{
	fprintf(stderr,"Line:%d ",line);
	perror(err_string);
	exit(1);
}

void handler(int signo)
{
	printf("this is handler\n");
}
int main()
{
	//安装信号处理函数
	if(SIG_ERR == signal(SIGINT,handler))
	{
		my_err("signla",__LINE__);
	}
	sleep(10);
	//屏蔽SIGINT
	sigset_t newmask, oldmask, pendmask;
	
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);

	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) == -1)
	{
		my_err("sigprocmask",__LINE__);
	}
	else
	{
		printf("set blocked\n");
	}
	
	sleep(10);
	//检查未决队列是否还存在SIGINT
	
	sigpending(&pendmask);
	switch(sigismember(&pendmask,SIGINT))
	{
		case 1:
			printf("pending has SIGINT\n");
			break;
		case 0:
			printf("pending do not have SIGINT\n");
			break;
		case -1:
			printf("pending use err\n");
			break;
	}
	
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) == -1)
	{
		my_err("sigprocmask",__LINE__);
	}
	else
	{
		printf("set unblocked\n");
	}
	while(1)
	{
		sleep(1);
	}
	return 0;
}
