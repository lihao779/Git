#include <unistd.h>
#include <iostream>

template<typename T>
void print(std::ostream& os, const T& t1)
{
    os << t1 ;
}

template<typename T, typename... Avgs>
void print(std::ostream& os, const T& t1, const Avgs& ... t2)
{
    std::cout << sizeof...(t2) << std::endl;
    std::cout << sizeof...(Avgs) << std::endl;
    os << t1 << ",";
    print(os, t2...);
    sleep(10);
}


#include <string>

int main()
{
    std::string s1 = "hello";
    int i = 1, j = 2;
    std::string s2 = "world";
    print(std::cout, s1, i, j, s2);
    
    return 0;
}
