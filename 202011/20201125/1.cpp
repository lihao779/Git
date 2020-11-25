#include <iostream>

using namespace std;



class Base
{
    public:
        void TestFun()
        {
            cout<<"Base::TestFun()"<<endl;
        }
        void func()
        {

        }
        int _b;
};

class Derived:public Base
{
    public:
        void TestFun(int a)
        {
            Base::_b = 10;
            cout<<"Derived::TestFun()"<<endl;
        }
        char _b;
};
int main()
{
    Derived d;
    Base b;
    Base* pb = &d;
    

    cout<<sizeof(d)<<endl;
    d._b = 1;
    d.Base::_b = 1;
    d.TestFun(1);
    d.Base::TestFun();
    
    return 0;
}
