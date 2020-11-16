#include<queue>
#include<iostream>
using namespace std;

int main()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    cout<<q.front()<<endl;
    cout<<q.back()<<endl;
    q.back() = 10;
    q.front() = 0;

    q.pop();
    q.pop();
    cout<<q.front()<<endl;
    cout<<q.back()<<endl;

    return 0;
}
