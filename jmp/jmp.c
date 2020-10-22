#include<stdio.h>
#include<setjmp.h>
#include<unistd.h>
#include<signal.h>
jmp_buf env;


void handler(int signo)
{
	printf("i am handler\n");
	siglongjmp(env,1);	
}
int main()
{
	
	switch(sigsetjmp(env,1))
	{
		case 0:
			printf("this is main\n");
			break;
		case 1:
			printf("this is jmp here\n");
			break;
		default:
			break;
	}
	signal(2,handler);
	while(1)
	{
		sleep(1);
	}
	return 0;
}
