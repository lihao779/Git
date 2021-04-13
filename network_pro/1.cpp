
#include <iostream>

union 
{
    short a;
    char ch[sizeof(a)];
}un;

int main()
{
    un.a = 0x0102;
    if(un.ch[0] == 1 && un.ch[1] == 2)
    {
        std::cout << "big -endian" << std::endl;
    }
    else if(un.ch[0] == 2 && un.ch[1] == 1)
    {
        std::cout << "little -endian" << std::endl;
    }
    else
    {
        std::cout << "unkonwn" << std::endl;
    }
    return 0;
}
