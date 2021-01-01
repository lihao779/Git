#include <iostream>

using namespace std;

class Base
{
public:
    Base()
    {
        cout<<"Base()"<<endl;
    }
    virtual ~Base()
    {
        cout<<"~Base()"<<endl;
    }
};
class Derived : public Base
{
    public:
        Derived()
            :p(new int[10])
        {
            cout<<"Derived()"<<endl;
        }
        ~Derived()
        {
            if(p)
            {
                delete[] p;
                p = NULL;
                cout<<"~Derived()"<<endl;
            }
        }
        int* p;

};


int main()
{
    Base* pb = new Derived();
    delete pb;
    return 0;
}
