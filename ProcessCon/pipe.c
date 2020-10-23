#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int fd[2];
	if(pipe(fd)<0)
	{
		perror("pipe");
		exit(1);
	}
	pid_t pid = fork();

	if(pid<0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid ==0)
	{
		close(fd[0]);
		char buf[100] = "linux";
		int len = strlen(buf);
		write(fd[1],buf,len);
	}
	else
	{
		int status;
		close(fd[1]);
		char buf[100] = {0};
		wait(&status);
		read(fd[0],buf,sizeof(buf)-1);
		printf("buf = %s\n",buf);
		memset(buf,0,sizeof(buf));
		read(fd[0],buf,sizeof(buf)-1);
		printf("buf = %s\n",buf);
	}
	return 0;
}
