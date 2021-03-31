#include "Vector.hpp"
#include <iostream>
int main()
{
    int array[] = {1, 2, 3, 4, 5};
    Vector<int> v1;
    Vector<int> v2(10, 2);
    Vector<int> v3(array, array + sizeof(array)/sizeof(int));
    Vector<int> v4(v3);
    for(auto& e: v1)
        std::cout << e << " ";
    std::cout << std::endl;
    for(auto& e: v2)
        std::cout << e << " ";
    std::cout << std::endl;
    for(auto& e: v3)
        std::cout << e << " ";
    std::cout << std::endl;
    for(auto& e: v4)
        std::cout << e << " ";
    std::cout << std::endl;
    v1 = v2;
    for(auto& e: v1)
        std::cout << e << " ";
    std::cout << std::endl;
    std::cout << "v1.size:" << v1.size() << " v1.capacity:" << v1.capacity()<< std::endl;
    v2.swap(v3);
    for(auto& e: v2)
        std::cout << e << " ";
    std::cout << std::endl;
    for(auto& e: v3)
        std::cout << e << " ";
    std::cout << std::endl;
    v3[0] = 100;
    std::cout << v3[0] << std::endl;
    v3.front() = 10;
    std::cout << v3[0] << std::endl;
    std::cout << v3.back() << std::endl;
    v3.assign(array, array + sizeof(array)/sizeof(int));
    for(auto& e: v3)
        std::cout << e << " ";
    std::cout << std::endl;
    v3.push_back(1);
    std::cout << v3.back() << std::endl;
    v3.pop_back();
    std::cout << v3.back() << std::endl;
    
    v3.insert(v3.begin(), array, array + sizeof(array)/sizeof(int));
    std::cout << "v3.size:" << v3.size() << " v3.capacity:" << v3.capacity()<< std::endl;
    for(auto& e: v3)
        std::cout << e << " ";
    std::cout << std::endl;
    v3.erase(v3.begin(), v3.end());
    if(v3.empty())
        std::cout << "v3 is empty" << std::endl;


    
    return 0;
}
