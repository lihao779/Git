#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
int main()
{
    /*
    struct sockaddr_in sock;
    memset(&sock,0,sizeof(sock));
    sock.sin_family = AF_INET;
    sock.sin_port = htos(80);
    if(0 < inet_aton("172.17.242.131",&sock.sin_addr))
    {
        perror("inet_aton");
        return 1;
    }
    connect(sock_fd,(struct sockaddr*)&sock,sizeof(struct sockaddr_in));
    */

    struct sockaddr_in sock;
    memset(&sock,0,sizeof(struct sockaddr_in));
    sock.sin_family = AF_INET;
    sock.sin_port = htons(80);
    sock.sin_addr = htonl(INADDR_ANY);

    bind(sock_fd,(struct sockaddr*)&sock,sizeof(struct sockaddr_in));



    return 0;
}
