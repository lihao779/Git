#include <iostream>

using namespace std;

class Base
{
    public:
        virtual void func(int val = 0)
        {
            cout<<"Base::func("<<val<<")"<<endl;
        }
        virtual void test()
        {
            func();
        }
};

class Derived : public Base
{
    public:
        virtual void func(int val = 1)
        {
            cout<<"Derived::func("<<val<<")"<<endl;
        }
        virtual void test()
        {
            func();
        }
};

int main()
{
    Derived* d = new Derived;
    d->test();
    return 0;
}
