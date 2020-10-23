/*
// 原版
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd = open("./fifo",O_WRONLY);
	if(fd < 0)
	{
		printf("open failed\n");
	}
	else
	{
		write(fd,"linux",5);
		printf("open success\n");
	}

	close(fd);
	return 0;
}
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

#define FIFO_NAME "fifo"
#define BUF_SIZE 1024

int main()
{
	char buf[BUF_SIZE] = "Hello";
	int fd;
	
	umask(0);
	if(mkfifo(FIFO_NAME,S_IFIFO|0666) < 0)
	{
		perror("mkfifo");
		exit(1);
	}
	
	fd = open(FIFO_NAME,O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}

	write(fd,buf,strlen(buf)+1);//记得写管道吧\0写进去

	close(fd);

}
