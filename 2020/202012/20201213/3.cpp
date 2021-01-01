#include <iostream>
using namespace std;

class A
{
    public:
    virtual void f1() = 0;//类中只可以写声明，定义无意义想写只能写到类外

};
void A::f1()
{}


int main()
{
    return 0;
}
