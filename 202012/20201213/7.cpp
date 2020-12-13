#include <iostream>
using namespace std;
/*
class A
{
    public:
        void f1(A a)
        {
            a._a = _a;
        }
    private:
        int _a;
};

int main()
{
    return 0;
}
*/
class A
{
    public:
    A()
    {
        cout<<"A()"<<endl;
    }
    A(const A& a)
    {
        cout<<"A(const A&)"<<endl;
    }
    int _a;
};
class B:public A
{
    public:
    B()
    {
        cout<<"B()"<<endl;
    }
    B(const B& b)
        :A(b)
    {
        cout<<"B(const B&)"<<endl;
    }
    int _b;
};


int main()
{
    B b;
    B d(b);
    return 0;
}
