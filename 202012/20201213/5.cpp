#include <iostream>
#include <stdio.h>
using namespace std;

void Test(int* p)
{
    delete p;
}
void Swap(int*& p1,int*& p2)
{
    int* temp = p1;
    p1 = p2;
    p2 = temp;
}
int main()
{
    int a,b;
    int* p1 = &a;
    int* p2 = &b;
    Swap(p1,p2);
    cout<<&a<<" "<<p1 <<endl;
    cout<<&b<<" "<<p2<<endl;
    int* ptr = new int();
    Test(ptr);
    return 0;

}
