#include <iostream>
using namespace std;

class Base
{
    public:
        virtual void Testfunc()
        {
            cout<<"Base::Testfunc"<<endl;
        }
};

class Derived : public Base
{
    public:
        virtual void Testfunc()override
        {
            cout<<"Derived::Testfunc"<<endl;
        }
        
        
};

class A
{
    public:
        static A* Get(int a)
        {
            return  new A(a);
            
        }
        static void Destory(A* a)
        {
            delete a;
        }
    private:
        A(int a)
            :_a(a)
        {}
        int _a;
}; // 一个不可以被继承的类

int main()
{
    A* ptr = A::Get(1);
    A::Destory(ptr);
    return 0;
}


/*
class B : public A
{
    public:
        B(int a,int b)
            :A(a)
             ,_b(b)
        {}
        int _b;
};
*/

