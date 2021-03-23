#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

class HasPtr
{
    public:
        HasPtr(const string& s = string())
            :ps(new string(s))
             ,i(0)
    {
        cout << "HasPtr(const string& s) " << this << endl;
    }
        //HasPtr(const HasPtr& s)
        //    :ps(new string(*s.ps))
        //     ,i(s.i)
        //{}
        //HasPtr& operator=(const HasPtr& p)
        //{
        //    *ps = *p.ps;
        //    i = p.i;
        //    return *this;
        //}
        ~HasPtr()
        {
            cout << "~HasPtr()" << endl;
            delete ps;
        }

        
    public:
        string* ps;
        int i;
};


void f(HasPtr p)
{
//    HasPtr ret = p;
}

int main()
{
    HasPtr temp("hello");
    f(temp);
    if(nullptr == temp.ps)
        cout << temp.i << endl;
    sleep(10);
    return 0;
}
