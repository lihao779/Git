#include <stdio.h>
#include <iostream>

using namespace std;

class Base
{
    public:
        void f0()
        {
            cout<<"Base::Testfunc0"<<endl;
        }
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
    public:
        void f0()
        {
            cout<<"Base::Testfunc0"<<endl;
        }
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
        //virtual void Testfunc3()
        //{
        //    cout<<"Derived::Testfunc3"<<endl;
        //}
        virtual void Testfunc5()
        {
            cout<<"Derived::Testfunc5"<<endl;
        }


};

void TestVirtual(Base& b)
{
    b.f0();
    b.Testfunc1();
    b.Testfunc2();
    b.Testfunc3();
}

void Test1()
{
    Base b;
    Derived d;
    Base* bb = (Base*)&d;
    bb->Testfunc1();
    b = (Base)d;
    bb = &b;
    bb->Testfunc1();
}


int main()
{
    Test1();
    Base b;
    Derived d;
    TestVirtual(b);
    cout<<endl;
    TestVirtual(d);
    return 0;
}



/*
typedef void(*PVF)();
void Test(Base& b,std::string s)
{
   cout << s << endl;
   PVF* p = (PVF*)(*(long long*)(&b)); 
   while(*p)
   {
       (*p)();
       p++;
   }
}


int main()
{
     Base b;
    // Test(b,"Base");
    Derived d;
    printf("%p,%p\n",(int*)&b,(int*)&d);
    Test(d,"Derived");
    return 0;
}
*/
