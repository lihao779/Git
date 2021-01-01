#include "../udp.hpp"
#include <iostream>
int main()
{
    class UdpApi svr;
    svr.CreateSock();
    svr.IP_Port_bind("192.168.40.131",19999);
    while(1)
    {
        char buf[1024] = {0};
        svr.Recv_message_svr(buf,sizeof(buf));
        cout<<"cil:"<<buf<<endl;
        memset(buf,0,sizeof(buf));
        cout<<"svr:";
        cin>>buf;
        svr.Send_message_svr(buf);
    }
    return 0;
}
