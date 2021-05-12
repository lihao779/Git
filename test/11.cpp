#include <iostream>
using namespace std;

class A
{
public:
    virtual void fun1()
    {
        cout << "fun1" << endl;
    }
    virtual void fun2()
    {
        cout << "fun2" << endl;
    }
    virtual void fun3()
    {
        cout << "fun3" << endl;
    }
};


typedef void(*PFun)();
int main()
{
    A a;
    PFun Pfun;
    Pfun = (PFun)*(((long int*)(*((long int*)&a))) + 0);
    Pfun();
    Pfun = (PFun)*(((long int*)(*((long int*)&a))) + 1);
    Pfun();
    Pfun = (PFun)*(((long int*)(*((long int*)&a))) + 2);
    Pfun();
    return 0;
}
