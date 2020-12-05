#include <iostream>
using namespace std;

class Base
{
    public:
        Base(int a)
            :_a(a)
        {
            cout<<"Base()"<<endl;
        }
        virtual ~Base()
        {
            cout<<"~Base()"<<endl;
        }
        int _a;
};

class Derived : public Base
{
    public:
        Derived(int a,int b)
            :Base(a)
             ,_b(b)
        {
            ptr = new int[10];
            cout<<"Derived()"<<endl;
        }
        ~Derived()
        {
            if(ptr)
            {
                delete[] ptr;
                ptr = NULL;
                cout<<"~Derived"<<endl;
            }
        }
        int* ptr;
        int _b;
};
class A : public Derived
{
    public:
        A(int a,int b)
            :Derived(a,b)
        {
            cout<<"A"<<endl;
        }
        ~A()
        {
            cout<<"~A"<<endl;
        }
};

int main()
{
    Base* base= new A(1,2);
    delete base;

    return 0;
}

