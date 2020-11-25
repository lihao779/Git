#include <iostream>
using namespace std;

class Base
{
    public:
        Base()
        {
            cout<<"Base()"<<endl;
        }
        ~Base()
        {
            cout<<"~Base()"<<endl;
        }
        static void Get()
        {
            cout<<"  "<<endl;
        }
        static int c ;
        int _b;

};
int Base::c = 1;

class Derived : public Base
{
    public:
        Derived()
        {
            cout<<"Derived()"<<endl;
        }
        ~Derived()
        {
            cout<<"~Derived"<<endl;
        }
        int _d;
};

int main()
{
    cout<<sizeof(Derived)<<endl;
    Base b;
    Derived d;
    
    b.c = 1;
    d.c = 2;
    d.Get();
    cout<<&b.c<<" "<<&d.c<<endl;
    return 0;
}

/*
class Base
{
    public:
        Base(int b = 1)
            :_b(b)
        {
            cout<<"Base()"<<endl;
        }
        ~Base()
        {
            cout<<"~Base()"<<endl;
        }

        int _b;
};

class Derived : public Base
{
    public:
        Derived(int b,int d)
            :Base(b)//派生类记得再初始化列表调用基类的构造
             ,_d(d)
        {
            cout<<b;
            cout<<"Derived"<<endl;
        }
        ~Derived()
        {
            cout<<"~Derived"<<endl;
        }

/*
class Base
{
    public:
        Base()
        {
            cout<<"Base()"<<endl;
        }
        ~Base()
        {
            cout<<"~Base()"<<endl;
        }
        Base(const Base& b)
            :_b(b._b)
        {
            cout<<"Base(const Base& b)"<<endl;
        }
        Base& operator=(const Base& b)
        {
            cout<<"Base::operator="<<endl;
            if(this != &b)
            {
                _b = b._b;
            }
            return *this;
        }
/*
class Base
{
    friend void Func();//友元关系不能继承到子类
    public:
        Base()
        {
            cout<<"Base()"<<endl;
        }
        ~Base()
        {
            cout<<"~Base()"<<endl;
        }
    private:
        int _b;
};

class Derived : public Base
{
    public:
        Derived()
        {
            cout<<"Derived()"<<endl;
        }
        ~Derived()
        {
            cout<<"~Derived"<<endl;
        }
    private:
        int _d;
};

void Func()
{
    Base b;
    b._b = 10;
}
int main()
{
    Func();
    return 0;
}
*/


/*
class Base
{
    public:
        Base(int b = 1)
            :_b(b)
        {
            cout<<"Base()"<<endl;
        }
        ~Base()
        {
            cout<<"~Base()"<<endl;
        }

        int _b;
};

class Derived : public Base
{
    public:
        Derived(int b,int d)
            :Base(b)//派生类记得再初始化列表调用基类的构造
             ,_d(d)
        {
            cout<<b;
            cout<<"Derived"<<endl;
        }
        ~Derived()
        {
            cout<<"~Derived"<<endl;
        }

/*
class Base
{
    public:
        Base()
        {
            cout<<"Base()"<<endl;
        }
        ~Base()
        {
            cout<<"~Base()"<<endl;
        }
        Base(const Base& b)
            :_b(b._b)
        {
            cout<<"Base(const Base& b)"<<endl;
        }
        Base& operator=(const Base& b)
        {
            cout<<"Base::operator="<<endl;
            if(this != &b)
            {
                _b = b._b;
            }
            return *this;
        }
        int _b;
};

class Derived : public Base
{
    public:
        Derived()
        {
            cout<<"Derived()"<<endl;
        }
        ~Derived()
        {
            cout<<"~Derived"<<endl;
        }
        Derived(const Derived& b)
            :Base(b)   
            ,_d(b._d)
        {
            // Base(b);//报错
            cout<<"Derived(const Derived& d)"<<endl;
        }
        Derived& operator=(const Derived& b)
        {
            cout<<"Derived::operator="<<endl;
            if(&b!=this)
            {
                _d = b._d;
                Base::operator=(b);
            }
            return *this;
        }
        int _d;
};

int main()
{
    Derived d1;
    Derived d2(d1);
    d2 = d1;    
    return 0;
}
*/


/*
class Base
{
    public:
        Base(int b = 1)
            :_b(b)
        {
            cout<<"Base()"<<endl;
        }
        ~Base()
        {
            cout<<"~Base()"<<endl;
        }

        int _b;
};

class Derived : public Base
{
    public:
        Derived(int b,int d)
            :Base(b)//派生类记得再初始化列表调用基类的构造
             ,_d(d)
        {
            cout<<b;
            cout<<"Derived"<<endl;
        }
        ~Derived()
        {
            cout<<"~Derived"<<endl;
        }

        int _d;
};
void Test1(int a ,int b = 1,int c = 1)
{
    cout<<a<<b<<c<<endl;
}

int main()
{
    Derived d(1,2);

    int* p = new int[10];
    for(int i =0;i<10;i++)
    {
        cout<<*(p+i);
    }
    cout<<endl;
    delete[] p;

    return 0;
}
*/

