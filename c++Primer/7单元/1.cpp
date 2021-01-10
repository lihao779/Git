#include <iostream>
#include <string>

struct Sale_date
{
    std::string ISBN;
    int count;
    double totalPrice;
};

int main()
{
    Sale_date total;
    double price;

    if(std::cin>>total.ISBN>>total.count>>price)
    {
        total.totalPrice = price*total.count;
        Sale_date tmp;
        while(std::cin>>tmp.ISBN>>tmp.count>>price)
        {
            tmp.totalPrice = tmp.count*price;
            if(tmp.ISBN == total.ISBN)
            {
                total.count += tmp.count;
                total.totalPrice += tmp.totalPrice;
            }
            else
            {
                std::cout<<total.ISBN<<" "<<total.count<<" "<<total.totalPrice<<std::endl;
                total = tmp;
            }
        }
        std::cout<<total.ISBN<<" "<<total.count<<" "<<total.totalPrice<<std::endl;

    }
    else
    {
        std::cerr<<"No Date?"<<std::endl;
        return -1;
    }
    return 0;
}
