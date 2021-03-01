#include <unistd.h>
#include <iostream>
class Account
{
    public:
        static double initRate();
        static const int pried = 10;
    private:
        double money;
        static double interestRate;
        int array[pried];
};
const int Account::pried;
double Account::initRate()
{
    std::cout << "111" << std::endl;
    return 1;
}
double Account::interestRate = initRate();
class Bar
{
    public:
        Bar& bar3;
        Bar* bar4;
};
#include <vector>
class Example
{
    public:
        //static double rate = 6.5;
        static const int vecsize = 10;
        //static std::vector<int> vec(vecsize);
};

int main()
{
    auto old_status = std::cin.rdstate();
    std::cin.clear();
    int ra = 1;
    std::cin >> ra;
    auto new_status = std::cin.rdstate();
    std::cin.setstate(old_status);
    std::cin.clear();
    auto new_status1 = std::cin.rdstate();
    std::cout << old_status << " " << new_status << " " << new_status1<< std::endl;
    sleep(10);
    return 0;
}

