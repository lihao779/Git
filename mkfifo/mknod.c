
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
int main()
{
	umask(0);
//mknod	
	/*
	if(mknod("./fifo",S_IFIFO,0)<0)
	{
		printf("failed\n");

	}
	*/
//mkfifo
	if(mkfifo("./fifo",S_IFIFO|0664) < 0)
	{
		printf("failed\n");
	}


	return 0;
}
