#include <iostream>
#include <string>

using namespace std;


class Person
{
    public:
        Person(string name, int age)
            :name_(name) , age_(age)
        {}

        void print()
        {
            cout << name_ << ":" << age_ << endl;
        }
    private:
        string name_;
        int age_;
};

class Student : public Person
{
    public:
        Student(string name, int age)
            :Person(name, age)
        {}
    void Test()
    {
        print();
    }
};

int main()
{
    Person p("xxx", 8);
    return 0;
}
