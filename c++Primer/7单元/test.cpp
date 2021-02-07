#include <iostream>
class A
{
    public:
    A(int a = int())
    :a_(a)
    {}
    int Geta()
    {
        return a_;
    }
    private:
    int a_;
};

int main()
{
    A a(2);
    std::cout << a.Geta() << std::endl;
    A b;
    std::cout << b.Geta() << std::endl;
    b = a;
    std::cout << a.Geta() << std::endl;
    std::cout << b.Geta() << std::endl;
    return 0;
}
