#include <iostream>

using namespace std;

class Person
{
    public:
    virtual void tick()
    {
        cout<<"全价票"<<endl;
    }
};
class Student:public Person
{
    public:
        virtual void tick()
        {
            cout<<"半价票"<<endl;
        }
};
class Army:public Person
{
    public:
        virtual void tick()
        {
            cout<<"免费票"<<endl;
        }
};
class A:public Army
{};


void Test(Person* p)
{
    p->tick();
}
void Test(Person& p)
{
    p.tick();
}
int main()
{
    Person p;
    Student s;
    Army a;
    Test(&p);
    Test(&s);
    Test(&a);
    Test(p);
    Test(s);
    Test(a);
    Person* ptr1 = &p;
    ptr1->tick();
    Person* ptr2 = &s;
    ptr2->tick();
    Person* ptr3 = &a;
    ptr3->tick();
    Person& rptr1 = p;
    rptr1.tick();
    Person& rptr2 = s;
    rptr2.tick();
    Person& rptr3 = a;
    rptr3.tick();
    return 0;
}
