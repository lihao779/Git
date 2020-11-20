#include<iostream>
#include<vector>
using namespace std;

int main()
{
    /*
    vector<int> v{1,2,3,4,5};
    auto it = v.cbegin();
    while(it != v.cend())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;;
    */
    vector<int> v(10,5);
    auto it = v.begin();
    /*
    while(it!=v.end())
    {
        *it *=2;
        cout<<*it<<endl;
        it++;
    }
    */
    for(auto it = v.begin();it!=v.end();it++)
    {
        *it *=2;
        cout<<*it<<" ";
    }
    return 0;
}
