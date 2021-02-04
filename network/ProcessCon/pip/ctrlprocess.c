#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char* argv[])
{
	/*
	for(int i = 0;i<argc;i++)
	{
		printf("argv[%d] = %s\n",i,argv[i]);
	}
	*/

	char buf[1024] = {0};
	int n ;
	printf("this is ctrlprocess\n");
	while(1)
	{
		if((n = read(0,buf,sizeof(buf)-1))>0)
		{
			buf[n] = '\0';
			if(!strcmp(buf,"exit"))
				break;
			if(!strcmp(buf,"getpid"))
			{
				printf("my process pid is %d\n",getpid());
				break;
			}
		}
	}
	printf("ctrlprocess end\n");

	return 0;
}
