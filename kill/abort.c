#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
void handler(int signo)
{
	while(1)
	{
		sleep(1);
	}
	printf("recv SIGABRT");
}

int main()
{
	signal(SIGABRT,handler);
	abort();
	while(1)
	{
		sleep(1);
	}
	return 0;
}
