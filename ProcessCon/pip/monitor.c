#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>

int main(int argc,char* argv[],char** environ)
{
	
	int fd[2];
	int pid;
	int status;

	if(argc<2)
	{
		printf("wrong parameter\n");
		exit(0);
	}
	if(pipe(fd)<0)
	{
		perror("pipe");
		exit(1);
	}
	
	pid = fork();
	if(pid<0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0)
	{
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);//注意1

		execve("./ctrlprocess",argv,environ);//注意2
		exit(0);//注意3
	}
	else
	{
		close(fd[0]);
		write(fd[1],argv[1],strlen(argv[1]));

	}

	wait(&status);//注意4

	return 0;
}

//注意1：子进程记得关闭不需要的文件描述符防止文件泄露
//注意2：execve第二个参数指定了传递给新程序的命令行参数，该数组参数argv[0]一般对应命令名
//数组最后一个元素argv[end]一般为NULL，也可不传最后一个NULL
//注意3：子进程进行程序切换时记得程序切换后exit(0)，以防止切换不成功导致执行下面代码造成混乱
//注意4：调用fork函数父进程一定要wait等待，防止产生僵尸进程
