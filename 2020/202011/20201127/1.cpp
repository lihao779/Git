#include <iostream>

using namespace std;

class A
{
    public:
        void Test(float a )
        {
            cout<<"A:a"<<a<<endl;
        }
};
class B:public A
{
    public:
        void Test(int b )
        {
            cout<<"B:b"<<b<<endl;
        }
};
int main()
{
    A* a = new A;
    B* b = new B;
    a = b;
    a->Test(1.1);
    return 0;
}
