#include <iostream>
using namespace std;

class Base
{
    public:
        virtual void f1()
        {
            cout<<"Base::f1()"<<endl;
        }
        virtual Base* f2()
        {
            cout<<"Base::f2()"<<endl;
            return this;
        }
        virtual void f3()
        {
            cout<<"Base::f3()"<<endl;
        }
        void f4()
        {
            cout<<"Base::f4()"<<endl;
        }
        void f5()
        {
            cout<<"Base::f5()"<<endl;
        }
        virtual int f6()
        {
            cout<<"Base::f6()"<<endl;
            return 0;
        }
        int f7()
        {
            cout<<"Base::f7()"<<endl;
            return 0;
        }

};
class Derived : public Base
{
    public:
        virtual void f1()override
        {
            cout<<"Derived::f1()"<<endl;
        }
        virtual Derived* f2()override
        {
            cout<<"Derived::f2()"<<endl;
            return this;
        }

        // 同名隐藏
        virtual void f3(int )
        {
            cout<<"Derived::f3()"<<endl;
        }
        virtual void f4()
        {
            cout<<"Derived::f4()"<<endl;
        }
        void f5()
        {
            cout<<"Derived::f5()"<<endl;
        }
        // 错误写法f6在基类中为虚函数
        // 子类中必须返回值一样--不然报错
        
        /*
        virtual void f6()
        {
            cout<<"Derived::f5()"<<endl;
        }
        */ 
        char f7()
        {
            cout<<"Derived::f7()"<<endl;
            return 0;
        }
};


int main()
{
    Base* ptr = new Derived;
    ptr->f1();
    ptr->f2();
    ptr->f3();
    ptr->f4();
    ptr->f5();
    ptr->f6();
    ptr->f7();


    return 0;
}
