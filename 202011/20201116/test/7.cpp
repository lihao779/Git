#include<iostream>
#include<string>
#include<list>
using namespace std;


int main()
{
    list<int> L;
    L.push_back(1);
    L.push_back(1);
    L.push_back(1);
    L.push_back(1);
    for(auto e:L)
    {
        cout<<e<<endl;
    }
    return 0;
}
