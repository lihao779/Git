#include <typeinfo>
#include <iostream>
class Date
{
    public:
        Date()
            :a(1)
             ,b(1)
    {}
    int Add()
    {
        return a + b;
    }
    void Print()
    {
        std::cout<<typeid(this).name()<<std::endl;
        std::cout<<typeid(int).name()<<std::endl;
    }
    private:
        const int a;
        const int b;
};
class Date1
{
    public:
        Date1()
            :a(1)
             ,b(1)
    {}
    int Add()
    {
        return a + b;
    }
    void Print()const
    {
        std::cout<<typeid(this).name()<<std::endl;
        std::cout<<typeid(int).name()<<std::endl;
    }
    private:
         int a;
         int b;
};
int main()
{
    const Date1 dd;
    Date d;
    d.Print();
    dd.Print();
}
