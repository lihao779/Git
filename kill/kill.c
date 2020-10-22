#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
int main(int argc,char* argv[])
{
	if(argc!=4 && argc!=2)
	{
		printf("kill pid or kill -s signal pid\n");
		return 0;
	}
	int pid = 0;
	int signal = SIGTERM;//默认信号
	for(int i = 1;i<argc;i++)
	{
		if(strcmp(argv[i],"-s")==0)
		{
			signal = atoi(argv[i+1]);
			break;
		}
	}
	if(argc == 2)
	{
		pid = atoi(argv[1]);
	}
	else
	{
		pid = atoi(argv[3]);
	}

	if(-1 == kill(pid,signal))
	{
		printf("kill failed\n");
		return 0;
	}

	return 0;
}
