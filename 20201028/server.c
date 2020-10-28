#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>

void my_err(const char* str,int line)
{
    printf("line in %d:%s is failed\n",line,str);
    return ;
}



int main()
{
    struct sockaddr_in sock;
    memset(&sock,0,sizeof(sock));

    
    if(socket(AF_INET,SOCK_STREAM,0) < 0)
    {
        my_err("socker",__LINE__);
        exit(-1);
    }
    sock.sin_family = AF_INET;

    
    return 0;
}
