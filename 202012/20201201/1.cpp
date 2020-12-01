#include <iostream>
using namespace std;

class B
{
    public:
        int _b;
};
class C1:virtual public B
{
    public:
        int _c1;
};
class C2:virtual public B
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
    d._b = 1;
    d._c1 = 2;
    d._c2 = 3;
    d._d = 4;
    /*
    int* p = (int*)(*(int*)(&d));
    p++;
    *p = 2;
    */
    return 0;
}
