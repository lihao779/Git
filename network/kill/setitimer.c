#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/time.h>

void handler(int signo)
{
	switch(signo)
	{
		case SIGALRM:
			printf("recv SIGALRM\n");
			break;
		case SIGPROF:
			printf("recv SIGPROF\n");
			break;
		default:
			break;
	}
	return ;
}

int main()
{
	signal(SIGALRM,handler);
	signal(SIGPROF,handler);
	struct itimerval s;
	s.it_interval.tv_sec = 5;//第二次
	s.it_value.tv_usec = 0,1;
	s.it_value.tv_sec = 0;//第一次
	s.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL,&s,NULL);
	setitimer(ITIMER_VIRTUAL,&s,NULL);
	while(1)
	{
		sleep(1);
	}
	return 0;
}
