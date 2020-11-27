#include <iostream>

using namespace std;

class A
{
    public:
        virtual void test()
        {
            cout<<"A"<<endl;
        }
};
class B:public A
{
    public:
        virtual void test()
        {
            cout<<"B"<<endl;
        }
};
class C:public B
{
    public:
        void test()
        {
            cout<<"C"<<endl;
        }
};
void Test(A& a)
{
    a.test();
}

int main()
{
    A a;
    B b;
    C c;
    Test(a);
    Test(b);
    Test(c);
    return 0;
}
