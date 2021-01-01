#include <iostream>
using namespace std;
/*
//菱形继承
class B
{
    public:
        int _b;
};
class C1:public B
{
    public:
        int _c1;
};
class C2:public B
{
    public:
        int _c2;
};
class D:public C1,public C2
{
    public:
        int _d;
};


int main()
{
    D d;
    // d._b = 1;菱形继承的二义性
    return 0;
}
*/

//菱形虚拟继承
class B
{
    public:
        void fun()
        {

        }
        int _b;
};
class C1:virtual public B//虚拟继承
{
    public:
        int _c1;
};
class C2:virtual public B// 虚拟继承
{
    public:
        int _c2;
};
class D:public C1,public C2
{
    public:
        int _d;
};


int main()
{
    D d;
    int* p =(int*)(*(int*)&d);
    /*d._b = 1;
    d.fun();
    C1& c1 = d;
    C2& c2 = d;
    c1._b  = 1;
    c2._b = 3;
    cout<<d._b<<endl;
    */
    return 0;
}
