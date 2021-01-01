#include<iostream>
#include<stack>

using namespace std;



void TestStack1()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    cout<<s.top()<<endl;
    s.top() = 10;
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.top()<<endl;
    while(!s.empty())
    {
        s.pop();
    }
    cout<<s.size()<<endl;


}

int main()
{
    TestStack1();
    return 0;
}
