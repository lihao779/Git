#include<unistd.h>
#include <fcntl.h>
#include<stdio.h>

int main()
{
	int fd = open("tp",O_RDONLY);
	char buf[100];
	int ret = read(fd,buf,100);
	printf("ret = %d\n");
	printf("buf = %s\n",buf);
	return 0;
}
