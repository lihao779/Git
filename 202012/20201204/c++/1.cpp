#include <iostream>

using namespace std;


class Person
{
    public:
        virtual void buytick()
        {
            cout<<"全价票"<<endl;
        }
};
class Student:public Person
{
    public:
        virtual void buytick()
        {
            cout<<"半价票"<<endl;
        }

};
class Soidler:public Person
{
    public:
        virtual void buytick()
        {
            cout<<"免费票"<<endl;
        }

};


void Test(Person& p)
{
    p.buytick();
}

int main()
{
    Person per;
    Student stu;
    Soidler sol;
    Test(per);
    Test(stu);
    Test(sol);
    return 0;
}
