#include "ChatServer.hpp"

int main()
{
    ChatServer* cs = new ChatServer();
    cs->InitSvr();
    cs->Start();
    delete cs;
    return 0;
}
