#include <forward_list>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

using namespace std;


void Insertstring(forward_list<string> fstr,string s1,string s2)
{
    auto it = fstr.begin();
    auto prev = fstr.before_begin();
    while(it != fstr.end())
    {
        if(*it == s1)
        {
            fstr.insert_after(it,s2);
            break;
        }
        prev++;
        it++;
    }
    if(it == fstr.end())
        fstr.insert_after(prev,s2);
}

int main()
{
    vector<int> v = {1,2,3,4,5,6};
    auto it = v.begin();
    while(it != v.end())
    {
        if((*it) & 1)
        {
            it = v.erase(it);
        }
        else 
            it++;
    }
    for(auto e:v)
    {
        cout << e << " ";
    }
    cout << endl;
    cout << "---------------------" << endl;
    int ia[] = {1,2,3,4,5,6,7,8,9,10};
    vector<int> v1(ia,ia+(sizeof(ia)/sizeof(int)));
    list<int> l1(ia,ia+(sizeof(ia)/sizeof(int)));
    forward_list<int> fl = {1,1,2,3,1,5,1};
    
    auto it1 = v1.begin();
    auto it2 = l1.begin();
    auto prev = fl.before_begin();
    auto curr  = fl.begin();

    while(it1 != v1.end())
    {
        if(*it1 & 1)
        {
            it1 = v1.erase(it1);
        }
        else it1++;
    }
    while(it2 != l1.end())
    {
        if(*it2 & 1)
        {
            it2 = l1.erase(it2);
        }
        else it2++;
    }

    while(curr != fl.end())
    {
        if(*curr & 1)
        {
            curr = fl.erase_after(prev);
        }
        else
        {
            prev = curr;
            curr++;
        }
    }

    for(auto e : v1)
    {
        cout << e << " ";
    }
    cout << endl;
    for(auto e : l1)
    {
        cout << e << " ";
    }
    cout << endl;
    for(auto e : fl)
    {
        cout << e << " ";
    }
    cout << endl;

    return 0;
}
