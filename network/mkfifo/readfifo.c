/*
//原版
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd = open("./fifo",O_RDONLY);
	if(fd < 0)
	{
		printf("open failed\n");
	}
	else
	{
		char buf[1024] = {0};
		read(fd,buf,sizeof(buf)-1);
		printf("fifo content is %s\n",buf);
		printf("open success\n");
	}
	close(fd);
	return 0;
}
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define FIFO_NAME "fifo"
#define BUF_SIZE 1024

int main()
{
	int fd;
	char buf[BUF_SIZE] ;

	fd = open(FIFO_NAME,O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	
	int ret = 	read(fd,buf,sizeof(buf)-1);
	printf("ret  = %d ,readfifo is %s\n",ret ,buf);
	return 0;
}
