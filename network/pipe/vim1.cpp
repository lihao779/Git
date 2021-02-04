#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main()
{
	if(mkfifo("./tp",0664)==-1)
	{
		printf("mkfifo failed\n");
		return 0;
	}

	char buf[1024] = {0};
	strcpy(buf,"linux84");
	int len = strlen(buf);

	int fd = open("./tp",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return 0;
	}
	int ret = write(fd,buf,len);
	if(ret == -1)
	{
		perror("write");
		return 0;
	}
	memset(buf,0,sizeof(buf));
	printf("buf = %s\n",buf);

	int ret2 = read(fd,buf,sizeof(buf)-1);
	if(ret2 == -1)
	{
		perror("read");
		return 0;
	}
	printf("buf = %s\n",buf);
	close(fd);
	return 0;
}
