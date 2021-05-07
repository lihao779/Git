#include <iostream>

using namespace std;

class Base
{
    public:
        Base(int a = 0) : m_a(a)
        {
            cout << "Base::Base()" << endl;
        }
        ~Base()
        {
            cout << "Base::~Base()" << endl;
        }
    private:
        int m_a;
};

class Derived : public Base
{
    public:
        Derived(int d = 0) : m_d(d)
        {
            cout << "Derived::Derived()" << endl;
        }
        ~Derived()
        {
            cout << "Derived::~Derived()" << endl;
        }
    private:
        int m_d;
};


int main()
{
    Derived d;
    Base b;
    b = d;
    
    Base* pb = &d;
    Base& rb = d;
    return 0;
}
