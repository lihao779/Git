#include <iostream>
class A
{
    public:
        
        A() = default;
        A(const A& )
        {
            std::cout << "A(const A&)" << std::endl;
        }
        void Test(int a)
        {
            std::cout << "A::Test():" << a << std::endl;
        }
        void Test(char a)
        {
            std::cout << "A::Test():" << a << std::endl;
        }

        virtual ~A()
        {
            std::cout << "~A()" << std::endl;
        }
};

class B: public A
{
    public:
        B()
        {
            std::cout << "B()" << std::endl;
        }
        
        using A::Test;

        void Test(int a)
        {
            std::cout << "B::Test():" << a << std::endl;
        }
        virtual ~B()
        {
            std::cout << "~B()" << std::endl;
        }

};


int main()
{
    B b1;
    B b2(b1);
    return 0;
}
