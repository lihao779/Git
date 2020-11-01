#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>


#define BUF_SIZE 32
int main()
{
    unsigned int address = 0;
    int ret = 0;
    char buf[BUF_SIZE];
    int len =0;
    struct in_addr in;
    int host = 0;
    int network = 0;

    memset(buf,0,sizeof(buf));
    printf("please input your address:");
    fgets(buf,BUF_SIZE-1,stdin);
    len = strlen(buf);
    buf[len-1] = '\0';

    
   
    if((ret = inet_aton(buf,&in))==0)
    {
        perror("inet_aton");
        exit(1);
    }

    else
    {
        printf("inet_aton:\t0x%x\n",in.s_addr);
    }

    address = inet_addr(buf);
    printf("inet_addr:\taddress = 0x%x\n",address);

    address = inet_network(buf);
    printf("inet_network:\taddress = 0x%x\n",address);

    printf("inet_ntoa:\t %s\n",inet_ntoa(in));

    host = inet_lnaof(in);
    network = inet_netof(in);

    printf("inet_lnaof:\thost0x%x\n",host);
    printf("inet_netof:\tnetwork0x%x\n",network);

    in = inet_makeaddr(network,host);
    printf("inet_makeaddr:\tin0x%x\n",in.s_addr);
    
    return 0;
}
