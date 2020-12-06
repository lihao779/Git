#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


class Wcroom
{
    public:
        void manwc()const
        {
            cout<<"go to left"<<endl;
        }
        void womanwc()const
        {
            cout<<"go to right"<<endl;
        }
};

// 抽象类
class Person
{
    
    public:
        // 纯虚函数
        virtual void gotowc(const Wcroom& wc) = 0;
        virtual ~Person()
        {}
};


class Man: public Person
{
    public:
        virtual void gotowc(const Wcroom& wc)
        {
            wc.manwc();
        }

};
class Woman: public Person
{
    public:
        virtual void gotowc(const Wcroom& wc)
        {
            wc.womanwc();
        }

};
void Test(Person* p)
{
    Wcroom wc;
    p->gotowc(wc);
}

void Test1()
{
    Wcroom wc;
    Person* p = NULL;
    for(int i = 0 ; i < 10;i++)
    {
        if(rand()%2 == 0)
            p = new Woman;
        else 
            p = new Man;
        p->gotowc(wc);
        delete p;
        sleep(1);
    }
}
int main()
{
    // Person p;//抽象类不能实例化对象
    Man man;
    Woman woman;
    Test(&man);
    Test(&woman);
    Test1();
    return 0;
}
