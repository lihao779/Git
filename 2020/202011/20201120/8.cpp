#include<iostream>

using namespace std;


class Base
{
    public:
        void Set(int a)
        {
            _b = 10;
            cout<<_b<<endl;
        }
    private:
        int _b;
};
class Derive:public Base
{
    public:
      void Set()
        {
            Base::Set(10);
            _d = 100;
            cout<<_d<<endl;
        }
    private:
        int _d;
};

int main()
{
    Derive d;
    d.Set();
    //d.Base::Set();
    return 0;
}
