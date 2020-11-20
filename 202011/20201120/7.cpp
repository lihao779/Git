#include<string>
#include<iostream>
using namespace std;

/*
class Person
{
    public:
        void Eat()
        {
            cout<<"Eat()"<<endl;
        }
        void Sleep()
        {
            cout<<"Sleep()"<<endl;
        }
    private:
        string _name;
        string _gender;
    protected:
        int _age;
};

class Student:public Person
{
    public:
        void Study()
        {
            _age = 10;
            cout<<"Study()"<<endl;
        }
    private:
        int _stuid;
};
class A:public Student
{
    public:
        void Test()
        {
            _age = 20;
        }
};
int main()
{
    
    Student s;
    s.Eat();
    s.Sleep();
    cout<<sizeof(Student)<<endl;
    return 0;
}
*/
/*
 * 继承权限public:
 * 基类中Public成员在子类中也是Public----既可以在类外直接使用&可以在子类中直接使用
 * 基类中Protected成员在子类中也是Protected----不能再类外直接使用&可以在子类中直接使用
 * 基类中Private成员在子类中不可见--不能再类外直接使用&不能再子类中直接使用
 *
 * 继承权限protected
 * 基类中Public成员在子类中是Protected---不可在类外访问&可以在子类中访问
 * 基类中Protected成员在子类中还是Protected---不可以在类外访问&可以在子类中访问
 * 基类中Private成员在子类中不可见---不可以在类外访问&在子类中不可见
 * 
 * 继承权限private
 * 基类中Public成员在子类中是Private---不可再类外访问&可以在子类中访问
 * 基类中Protected成员在子类中是Private---不可再类外访问&可以在子类中访问
 * 基类中Private成员在子类中不可见---不可再类外访问&在子类中不可见
 */

/*
class Base
{
    public:
    Base(int pub=10,int pro=10,int pri=10)
    {
        _pub = pub;
        _pro = pro;
        _pri = pri;
    }
    public:
        int _pub;
    protected:
        int _pro;
    private:
        int _pri;
};
class Derive:protected Base
{
    public:
    void Test()
    {
        _pub = 20;
        _pro = 20;
    }

};
class A:public Derive
{
    void Test()
    {
        _pub =20;
        _pro = 20;
    }
};

int main()
{
    Derive d;
    return 0;
}
*/
/*
class Base
{
    public:
    Base(int pub=10,int pro=10,int pri=10)
    {
        _pub = pub;
        _pro = pro;
        _pri = pri;
    }
    public:
        int _pub;
    protected:
        int _pro;
    private:
        int _pri;
};
class Derive:private Base
{
    public:
    void Test()
    {
        _pub = 20;
        _pro = 20;
    }

};
class A:public Derive
{
    void Test()
    {
    }
};
int main()
{
    Derive d;
    return 0;
}
*/
/////////////
//忘记写继承权限
/*
class Base
{
    public:
    Base(int pub=10,int pro=10,int pri=10)
    {
        _pub = pub;
        _pro = pro;
        _pri = pri;
    }
    public:
        int _pub;
    protected:
        int _pro;
    private:
        int _pri;
};
class Derive1:Base//----忘记书写继承权限class默认继承权限是private
{
    public:
    void Test()
    {
        _pub = 20;
        _pro = 20;
    }

};
struct Derive2:Base//----忘记书写继承权限struct默认继承权限是public
{
    public:
    void Test()
    {
        _pub = 20;
        _pro = 20;
    }
};
class A:public Derive2
{
    void Test()
    {
        _pro = 20;
    }
};
int main()
{
    Derive1 d1;
    Derive2 d2;
    d2._pub = 1;

    return 0;
}
*/
class Person
{
    public:
        void Eat()
        {
            cout<<"Eat()"<<endl;
        }
        void Sleep()
        {
            cout<<"Sleep()"<<endl;
        }
    private:
        string _name;
        string _gender;
    protected:
        int _age;
};

class Student:public Person
{
    public:
        void Study()
        {
            _age = 10;
            cout<<"Study()"<<endl;
        }
    private:
        int _stuid;
};
//////////////
//赋值兼容规则--前提--必须是public的继承方式
//
//如果是public的继承方式
//子类对象和基类对象的关系：is-a（是一个）的关系 子类对象可以看作是一个基类对象
//
int main()
{
    Student s;
    Person p;
    
    //1.子类的对象可以给基类赋值，基类的对象不可以给子类赋值
    p = s;
    //s = p; //错误
    //2.子类的指针可以赋值给基类，基类的指针不可以赋值给子类
    //子类的引用可以赋值给基类，基类的引用不可以赋值给子类
    //基类指针(或者引用)允许指向子类对象，子类指针(或者引用)不允许访问基类对象
    Person* pp = &p;
    Person* pp1 = &s;
    //Student* sp1 = &p;//错误
    Person& rp = p;
    Student* sp = &s;
    Student& rs = s;
    pp = sp;
    rp = rs;
    //rs = rp;//错误
    //sp = pp;//错误
    return 0;
}

