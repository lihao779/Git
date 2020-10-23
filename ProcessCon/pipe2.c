#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void child_rw_pipe(int wd,int rd)
{
	char* message1 = "this is child";
	int len = strlen(message1);
	write(wd,message1,len);
	
	char message2[1024] = {0};
	read(rd,message2,sizeof(message2)-1);//若无数据此处会阻塞
	printf("child message2 = %s\n",message2);
}

void father_rw_pipe(int wd,int rd)
{
	char* message1 = "this is father";
	int len = strlen(message1);
	write(wd,message1,len);

	char message2[1024];
	read(rd,message2,sizeof(message2)-1);//若无数据此处会阻塞
	printf("father message2 = %s\n",message2);
}
int main()
{
	int pipe1[2],pipe2[2];
	if(pipe(pipe1) < 0)
	{
		printf("pipe1 failed\n");
		exit(1);
	}
	if(pipe(pipe2) < 0)
	{
		printf("pipe2 failed\n");
		exit(1);
	}

	pid_t pid = fork();
	int status;
	if(pid<0)
	{
		printf("fork failed\n");
		exit(1);
	}
	else if(pid == 0)
	{
		close(pipe1[0]);
		close(pipe2[1]);
		child_rw_pipe(pipe1[1],pipe2[0]);
		
		close(pipe1[1]);
		close(pipe2[0]);
	}
	else
	{
		close(pipe1[1]);
		close(pipe2[0]);
		father_rw_pipe(pipe2[1],pipe1[0]);
		wait(&status);
		close(pipe1[0]);
		close(pipe2[1]);
	}
	return 0;
}
////////////////////
//思考：由于先创建双匿名管道在创建父子进程，父子进程都拥有管道的读写描述符
//子进程关闭的两个读写文件标识符父进程均保持打开，父进程关闭的两个文件标识符子进程均保证打开
//所以两个匿名管道的read和write端都有一个文件标识符管理，所以write和read函数均可以阻塞
