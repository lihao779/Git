#include<unistd.h>
#include <fcntl.h>
#include<stdio.h>

int main()
{
	int fd = open("tp",O_WRONLY);
	char buf[100] = "hei";
	int ret = write(fd,buf,4);
	printf("ret = %d\n");
	return 0;
}
