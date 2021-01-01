#include<iostream>
#include<string>

void Test1()
{
    std::string s1("0123456789ABCDEF");
    std::string::size_type n ;
    std::string s2;
    while(std::cin>>n)
    {
        if(n<s1.size())
        {
            s2+=s1[n];
        }
    }
    std::cout<<s2<<std::endl;
}

void Test2()
{
    std::string s("0123456789");
    for(char& e:s)
    {
        e = 'x';
    }
    std::cout<<s<<std::endl;
    for(size_t i=0;i!=s.size();i++)
    {
        s[i] = 'x';
    }
    std::cout<<s<<std::endl;
}
void Test3()
{
    std::string s;
    std::cin>>s;
    for(size_t i =0;i<s.size();i++)
    {
        if(!ispunct(s[i]))
            std::cout<<s[i];
    }
    std::cout<<std::endl;
}
void Test4()
{
    const std::string s("keep out");
    for(auto& e:s)
    {
        std::cout<<e<<" " ;
    }
    std::cout<<std::endl;
}
int main()
{
    // Test2();
    // Test3();
    Test4();
    return 0;
}
