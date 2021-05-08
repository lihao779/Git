#include <iostream>

class A
{
    public:
        A() {}
        virtual void Test() {}
};

using namespace std;
int main()
{
    cout << sizeof(A) << endl;
    return 0;
}
