#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define FIFO_READ  "writefifo"
#define FIFO_WRITE "readfifo"
#define BUF_SIZE   1024

int main()
{
	int rfd,wfd;
	char buf[BUF_SIZE] = {0};

	if(mkfifo(FIFO_WRITE,S_IFIFO|0666) < 0)
	{
		perror("mkfifo");
		exit(1);
	}

	while(-1 == (rfd = open(FIFO_READ,O_RDONLY)))
	{
		sleep(1);
	}
	
	wfd = open(FIFO_WRITE,O_WRONLY);
	if(wfd < 0)
	{
		perror("open");
		exit(1);
	}

	while(1)
	{
		int len = read(rfd,buf,sizeof(buf));
		if(len > 0)
		{
			buf[len] = '\0';
			printf("Server:%s\n",buf);
		}
		printf("Client:");
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		if(strncmp(buf,"quit",4) == 0)
		{
			close(wfd);
			close(rfd);
			exit(0);
		}
		write(wfd,buf,strlen(buf));
	}
}
