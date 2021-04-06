
template<typename T,typename... Avg>
void f(const T& t1,const Avg& ... t2)
{
    
}
#include <iostream>

#include <string>
int main()
{
    int i = 0;
    double j = 0.0;
    std::string s = "111";

    f(i, j, s);
    return 0;
}
