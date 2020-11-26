#include <iostream>

using namespace std;
class B
{
    public:
    B()
    {
        cout<<"B()"<<endl;
    }
    int _b;
};
class C1 : virtual public B
{
    public:
        int _c1;
};
class C2 : virtual public B
{
    public:
        int _c2;
};
class D : public C1,public C2
{
    public:
        int _d;
};


int main()
{
    B b;
    D d;
    d.C1::_b = 1;
    d._c1 = 2;
    d.C2::_b = 3;
    d._c2 = 4;
    d._d = 5;
    cout<<sizeof(C1)<<endl;
    cout<<sizeof(d)<<endl;
    return 0;
}
/*
class B1
{
    public:
        int _b1;
};
class B2
{
    public:
        int _b2;
};
class D : public B1,public B2
{
    public:
        int _d;
};


int main()
{
    D d;
    cout<<sizeof(d)<<endl;
    d._b1 = 1;
    d._b2 = 2;
    d._d = 3;
    return 0;
}
*/
