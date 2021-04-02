template<typename T>

int compare(const T& left, const T& right)
{
    if(left < right) return 1;
    if(right < left) return -1;
    return 0;
}

template<typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& data)
{
    while(first != last)
    {
        if(*first == data)
            return first;
        first++;
    }
    return last;
}

#include <vector>
#include <iostream>
#include <list>
#include <string>
int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    auto it = find(vec.cbegin(), vec.cend(), vec[2]);
    if(it != vec.cend())
        std::cout << *it << std::endl;
    std::list<std::string> l{"hello", "world"};
    std::cout << *find(l.cbegin(), l.cend(), "hello");
    return 0;
}
