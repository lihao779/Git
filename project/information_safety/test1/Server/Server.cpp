#include <iostream>
#include <string>
#include "Server.hpp"


int main()
{
    Ser ser; 
    ser.InitFd();
    ser.CreateThread();
    
    std::string s;
    std::cin >> s;
    return 0;
}
