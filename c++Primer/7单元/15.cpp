#include <iostream>
#include <deque>
#include <list>
#include <vector>

std::vector<int>::iterator Isin(std::vector<int>& vec,int num)
{
    std::vector<int>::iterator it;
    while(it != vec.end())
    {
        if(*it == num)
            break;
        it++;
    }
    if(it != vec.end())
        return it;
    return vec.end();
}

int main()
{
    std::list<std::deque<int>> l;
    std::vector<int> vec(10);
    std::vector<int>::reference ra = vec[0];
    ra = 1;
    std::vector<int>::value_type a = vec[0];
    a = 2;
    std::cout << vec[0] << std::endl;
    *vec.begin() = 3;
    std::vector<int> v1;
    std::vector<double> v2(v1.begin(),v1.end());
    std::deque<int> v3;
    std::vector<double> v4(v3.begin(),v3.end());
    return 0;
}

