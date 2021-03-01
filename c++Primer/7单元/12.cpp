#include <stdio.h>
#include <unistd.h>
#include <iostream>
std::istream& input(std::istream& is)
{
    int ch;
    while(is >> ch)
        std::cout << ch;
    is.clear();
    return is;
}
int main()
{
    //input(std::cin);
    //int ch;
    //std::cin >> ch;
    //std::cout << ch;
    while(1)
    {
        std::cout << " " << std::ends << 2 <<std::endl;
        sleep(1);
    }
    return 0;
}
