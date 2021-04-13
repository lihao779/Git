#include <random>
#include <iostream>
#include <ctime>
int main()
{
    static std::default_random_engine e(time(0));
    for(int i = 0; i < 10; i++)
        std::cout << e() << " ";
    std::cout << std::endl;

    static std::uniform_int_distribution<int> u(0,9);
    for(int i = 0; i < 10; i++)
        std::cout << u(e) << " ";
    std::cout << std::endl;
    std::cout << e.min() << " " << e.max() << std::endl;
    
    return 0;
}
