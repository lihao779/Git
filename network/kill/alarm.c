#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void send_ip()
{
	printf("this is send_ip\n");
}
void handler(int signo)
{
	send_ip();
	alarm(3);

}
int main()
{
	signal(SIGALRM,handler);
	raise(SIGALRM);
	while(1)
	{
		sleep(1);
	}
	return 0;
}
