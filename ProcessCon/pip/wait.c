#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
int main()
{
	int status;
	pid_t pid = fork();
	if(pid > 0)
	{
		int	i = 13;
		while(i)
		{
			i--;
			sleep(1);
		}
	}
	else 
	{
		printf("i am child\n");
		sleep(3);
	}
	wait(&status);
	return 0;
}
//注意：为什么wait写到if外面也可以呢？
//如果是父进程先到达wait函数等待子进程结束释放资源
//如果是子进程先到达wait直接释放资源，不需要等待父进程
//综上，wait写到父进程if里面或者写到if外面都可以
