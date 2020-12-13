#include <iostream>

using namespace std;

class Base
{
    public:
        virtual void f1(){cout << "Base::f1()"<<endl;}
        virtual void f2(){cout << "Base::f2()"<<endl;}
        virtual void f3(){cout << "Base::f3()"<<endl;}
};

class Derived : public Base
{
    public:
        virtual void f4(){cout << "Derived::f4()"<<endl;}
        virtual void f1(){cout << "Derived::f1()"<<endl;}
        virtual void f3(){cout << "Derived::f3()"<<endl;}
        virtual void f5(){cout << "Derived::f5()"<<endl;}
};

void TestVirtual(Base* pb)
{
    pb->f1();
    pb->f2();
    pb->f3();
}
void TestVirtual1(Base pb)
{
    pb.f1();
    pb.f2();
    pb.f3();
}

int main()
{
    Base b;
    Derived d;
    TestVirtual(&b);
    TestVirtual(&d);
    return 0;
}
