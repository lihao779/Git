#include <iostream>

template<typename T>
void Test1(const T& t1, const T& t2)
{
    std::cout << "Test1::<typename T>" << std::endl;
}

template<>
void Test1(const int& t1, const int& t2)
{

}
template<size_t N, size_t M>
void Test1(const char(&t1)[N], const char(&t2)[M])
{
    std::cout << "Test1::<size_t N, size_t M>" << std::endl;
}

#include <string.h>
int main()
{
    const char* p1 = "zi";
    const char* p2 = "world";
    std::cout << strcmp(p1, p2);
    std::cout << strcmp("zi", "world");
    Test1(p1, p2);
    Test1("hi", "world");
    return 0;
}
