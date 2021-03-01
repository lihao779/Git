#include <stdio.h>
#include <unistd.h>
#include <iostream>
std::istream& input(std::istream& is)
{
    char ch;
    while(is >> ch)
        std::cout << ch;
    is.clear();
    return is;
}
#include <fstream>
#include <string>
#if 0
int main()
{
    //input(std::cin);
    //int ch;
    //std::cin >> ch;
    //std::cout << ch;
    //while(1)
    //{
    //    std::cout << " " << std::ends << 2 <<std::endl;
    //    sleep(1);
    //}
    *std::cin.tie() << 1 << std::endl;
    std::string file ("test.txt");
    std::ifstream in(file);
    in.close();
    sleep(1);
    return 0;
}
#endif
#include <vector>
#if 0
int main()
{
    std::vector<std::string> vec;
    std::ifstream in;
    in.open("test.cpp");
    if(in)
    {
        std::string s;
        while(in >> s) 
            vec.push_back(s);
    }
    else
        std::cout << "open failed" << std::endl;
    for(size_t i = 0;i < vec.size();i++)
    {
        std::cout << vec[i] << std::endl;
    }
    in.close();

    std::ofstream out;
    out.open("test.txt",std::ofstream::out | std::ofstream::trunc | std::ostream::app);
    out.close();
    return 0;
}
#endif
#include <sstream>
int main()
{
    std::vector<std::string> vec;
    std::ifstream in("test.txt");
    std::string s;
    while(getline(in,s))
    {
        vec.push_back(s);
    }
    for(size_t i = 0;i < vec.size();i++)
    {
        std::istringstream strin;
        strin.str(vec[i]);
        std::string temp;
        while(strin >> temp)
        {
            std::cout << temp << std::endl;
        }
    }
    return 0;
}
