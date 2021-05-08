#include <memory>
#include <iostream>



using namespace std;
class A
{
    public:
        A()
        {
            cout << "A()" << endl;
        }
        ~A()
        {
            cout << "~A()" << endl;
        }
};


class B : public A
{
    public:
        B()
        {
            cout << "B()" << endl;
        }
         ~B()
        {
            cout << "~B()" << endl;
        }
};


int main()
{
    shared_ptr<A> ptr1(new B);
    //A *pb = new B;
    //delete pb;
    return 0;
}
