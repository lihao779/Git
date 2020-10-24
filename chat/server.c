#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>


#define FIFO_READ  "readfifo"
#define FIFO_WRITE "writefifo"
#define BUF_SIZE   1024

int main()
{
	int len = 0;
	int wfd,rfd;
	char buf[BUF_SIZE] =  {0};
	if(mkfifo(FIFO_WRITE,S_IFIFO|0666) < 0)
	{
		perror("mkfifo");
		exit(1);
	}

	wfd = open(FIFO_WRITE,O_WRONLY);
	if(wfd == -1)
	{
		perror("open");
		exit(1);
	}

	while(rfd = open(FIFO_READ,O_RDONLY) == -1)
	{
		sleep(1);
	}

	while(1)
	{
		printf("Server:");
		fgets(buf,BUF_SIZE,stdin);
		len = strlen(buf);
		buf[len-1] = '\0';
		if(0 == strncmp(buf,"quit",4))
		{
			close(rfd);
			close(wfd);
			exit(0);
		}
		write(wfd,buf,strlen(buf));
		len = read(rfd,buf,BUF_SIZE);
		if(len > 0)
		{
			printf("len = %d\n",len);
			buf[len] = '\0';
			printf("Client:%s\n",buf);
		}

	}
	return 0;

}
