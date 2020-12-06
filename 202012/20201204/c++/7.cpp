#include <stdio.h>
#include <iostream>

using namespace std;

class Base
{
    public:
        virtual void Testfunc1()
        {
            cout<<"Base::Testfunc1"<<endl;
        }
        virtual void Testfunc2()
        {
            cout<<"Base::Testfunc2"<<endl;
        }
        virtual void Testfunc3()
        {
            cout<<"Base::Testfunc3"<<endl;
        }
};
class Derived: public Base
{
        virtual void Testfunc4()
        {
            cout<<"Derived::Testfunc4"<<endl;
        }

        virtual void Testfunc1()
        {
            cout<<"Derived::Testfunc1"<<endl;
        }
        virtual void Testfunc2()
        {
            cout<<"Derived::Testfunc2"<<endl;
        }
        virtual void Testfunc3()
        {
            cout<<"Derived::Testfunc3"<<endl;
        }
        virtual void Testfunc5()
        {
            cout<<"Derived::Testfunc5"<<endl;
        }


};


typedef void(*PVF)();

void Test()
{
    Base b;
 //   Derived d;

/*
    PVF* ptr = (PVF*)(*(int*)&d);
    while(*ptr)
    {
        printf("%p\n",*ptr);
        (*ptr)();
        ptr++;
    }

*/

    PVF* ptr = (PVF*)(*(int*)&b);
    while(*ptr)
    {
        printf("%p\n",*ptr);
        (*ptr)();
        ptr++;
    }

}


int main()
{
    Test();
    return 0;
}
