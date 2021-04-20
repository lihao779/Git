#include <unistd.h>
#include <errno.h>
size_t readn(int fd, void* vptr, size_t n)
{
    char* ptr = (char*)vptr;
    size_t nleft;
    size_t nread;
    nleft = n;
    while(nleft > 0)
    {
        if((nread = read(fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
            {
                nread = 0;
            }
            else
                return -1;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}
