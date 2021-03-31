#include <iostream>
#include "String.hpp"
int main()
{
    String s1;
    String s2("hello");
    //String s3("hello", 5);
    //String s4(5, 'c');
    //String s5(s2);
    //String s6(s2, 0, 5);
    //String s7(s2.begin(), s2.end());
    
    //std::cout << "s1.size:" << s1.size() << " s1.capacity:" << s1.capacity();
    //std::cout << " s1:" << s1 << std::endl;
    //std::cout << "s2.size:" << s2.size() << " s2.capacity:" << s2.capacity();
    //std::cout << " s2:" << s2 << std::endl;
    //std::cout << "s3.size:" << s3.size() << " s3.capacity:" << s3.capacity();
    //std::cout << " s3:" << s3 << std::endl;
    //std::cout << "s4.size:" << s4.size() << " s4.capacity:" << s4.capacity();
    //std::cout << " s4:" << s4 << std::endl;
    //std::cout << "s5.size:" << s5.size() << " s5.capacity:" << s5.capacity();
    //std::cout << " s5:" << s5 << std::endl;
    //std::cout << "s6.size:" << s6.size() << " s6.capacity:" << s6.capacity();
    //std::cout << " s6:" << s6 << std::endl;
    //std::cout << "s7.size:" << s7.size() << " s7.capacity:" << s7.capacity();
    //std::cout << " s7:" << s7 << std::endl;
    s1 = s2;
    std::cout << "s1.size:" << s1.size() << " s1.capacity:" << s1.capacity();
    std::cout << " s1:" << s1 << std::endl;
    s1 = String("hello");
    std::cout << "s1.size:" << s1.size() << " s1.capacity:" << s1.capacity();
    std::cout << " s1:" << s1 << std::endl;

    if(s1.empty())
        std::cout << "s1 is empty!" << std::endl;
    else
        std::cout << "s1 is not empty!" << std::endl;
    s1.resize(1);
    std::cout << "s1.size:" << s1.size() << " s1.capacity:" << s1.capacity();
    std::cout << " s1:" << s1 << std::endl;
    s1.reserve(10);
    std::cout << "s1.size:" << s1.size() << " s1.capacity:" << s1.capacity();
    std::cout << " s1:" << s1 << std::endl;

    s1.clear();
    if(s1.empty())
        std::cout << "s1 is empty!" << std::endl;
    s1 = "hello";
    s1[0] = 'w';
    std::cout << s1 << std::endl;
    s1.append(String(" world"));
    std::cout << s1 << std::endl;
    s1.assign(10, 'n');
    std::cout << s1 << std::endl;
    s1.replace(1, 2, String("hello"));
    std::cout << "---------" << std::endl;
    std::cout << s1 << std::endl;
    std::cout << "s1.size:" << s1.size() << " s1.capacity:" << s1.capacity();


    return 0;
}
