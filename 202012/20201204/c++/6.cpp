#include <iostream>

using namespace std;
class Base
{
    public:
    virtual void Testfun1()
    {
        cout<<"Base::Testfun1()"<<endl;
    }
    int _b;
};
class A
{
    public:
    void Test()
    {}
    int _a;
};

int main()
{
    cout<<sizeof(Base)<<endl;
    Base b;
    cout<<"&b"<<&b<<'\n'<<"&b._b"<<&b._b<<endl;
    A a;
    cout<<sizeof(A)<<endl;
    cout<<"&a"<<&a<<'\n'<<"&a._a"<<&a._a<<endl;
    return 0;
}
