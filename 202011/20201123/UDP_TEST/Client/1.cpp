#include "../udp.hpp"
#include <iostream>
int main()
{
    class UdpApi cil;
    cil.CreateSock();
    cil.IP_Port_cil("192.168.40.131",19999);
    while(1)
    {
        char buf[1024] = {0};
        cout<<"cil:";
        cin >> buf;
        cil.Send_message_cil(buf);
        memset(buf,0,sizeof(buf));
        cil.Recv_message_cil(buf,sizeof(buf));
        cout<<"svr:"<<buf<<endl;
    }
    return 0;
}
