#include <iostream>

using namespace std;

class B
{};
class C:public B
{};
class D:public C
{};
class Base
{
public:
    //只要子类用viratual标记则派生类的所有中不管加没加都是虚函数
    virtual void Testfun()
    {
        cout<<"Base::Testfun()"<<endl;
    }
    void Testfun1()
    {
        cout<<"Base::Testfun1()"<<endl;
    }
    virtual void Testfun2(int a)
    {
        cout<<"Base::Testfun2()"<<endl;
    }
    /*
    virtual void Testfun3()
    {
        cout<<"Base::Testfun3()"<<endl;
    }
    */
    virtual B* Testfun3()
    {
        cout<<"Base::Testfun3()"<<endl;
        return nullptr;
    }
    virtual void Testfun4()
    {
        cout<<"Base::Testfun4()"<<endl;
    }
    
};
class Derived: public Base
{
    public:
        void Testfun()
        {
            cout<<"Derived::Testfun()"<<endl;
        }
    virtual void Testfun1()
    {
        cout<<"Derived::Testfun1()"<<endl;
    }
    virtual void Testfun2()
    {
        cout<<"Derived::Testfun2()"<<endl;
    }
    /*-------编译不过
     * 要构成重写返回值类型必须相同 
    virtual int Testfun3()
    {
        cout<<"Derived::Testfun3()"<<endl;
        return 0;
    }
    */
    virtual C* Testfun3()
    {
        cout<<"Derived::Testfun3()"<<endl;
        return nullptr;
    }
    private:
    virtual void Testfun4()
    {
        cout<<"Derived::Testfun4()"<<endl;
    }
};
class A:public Derived
{
    public:
        void Testfun()
        {
            cout<<"A::Testfun()"<<endl;
        }
    virtual void Testfun1()
    {
        cout<<"A::Testfun1()"<<endl;
    }
    virtual void Testfun2()
    {
        cout<<"A::Testfun2()"<<endl;
    }
};

void Test(Base& b)
{
    b.Testfun();
    b.Testfun3();
    b.Testfun4();
}
void Test1(Derived& d)
{
    d.Testfun1();
}
void Test2(Base& b)
{
    b.Testfun2(1);
}
int main()
{
    Base b;
    Derived d;
    A a;
    Test(b);
    Test(d);
    /*
    Test(b);
    Test(d);
    Test(a);
    Test1(d);
    Test1(a);
    Test2(b);
    Test2(d);
    Test2(a);
    */
    return 0;
}
/* 重写（子类虚函数必须用virtual修饰）
 * 
 * 函数名字相同，返回值类型相同，参数列表相同
 * 例外
 * 1.子类返回子类的指针，基类返回基类的指针---任意对象的子类和基类都可以，
 * 没必要是自己的
 * 
 */


