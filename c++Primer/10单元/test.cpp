#include <cstdarg>
#include <iostream>

using namespace std;


class A
{
    public:
        A(){}
        ~A(){}

        void f1(int a,...)
        {
            va_list ap;
            va_start(ap,a);
            int result = 0;
            for(int i = 0;i < a;i++)
            {
                result += va_arg(ap,int);
            }
            return ;
        }
        void f2()
        {
            int a;
            cin >> a;
        }
};

int main()
{
    A a;
    a.f1(1,1);
    a.f2();
    return 0;
}
