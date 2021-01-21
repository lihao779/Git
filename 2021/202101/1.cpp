#include <iostream>
auto Add(int left,int right) ->int
{
    return left + right;
}

int main()
{
    std::cout<<Add(1,2)<<std::endl;
    return 0;
}
