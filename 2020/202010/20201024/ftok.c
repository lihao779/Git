#include<stdio.h>
#include<sys/ipc.h>

int main()
{
	for(int i = 1;i < 5;i++)
	{
		printf("key[%d] = %ul\n",i,ftok(".",i));
	}
	return 0;
}
