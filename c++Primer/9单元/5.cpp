
#include <forward_list>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

using namespace std;
int main()
{
    vector<int> vec = {1,2,3,4,5,6};
    list<int> l = {1,2,3,4,5};
    forward_list<int> fl = {1,2,3,4,5};
    auto it = vec.begin();
    auto it1 = l.begin();
    auto cur = fl.begin();
    auto prev = fl.before_begin();
    while(it != vec.end())
    {
        if(*it & 1)
        {
            it = vec.insert(it,*it);
            it+=2;
        }
        else
        {
            it = vec.erase(it);
        }
    }
    while(it1 != l.end())
    {
        if(*it1 & 1)
        {
            it1 = l.insert(it1,*it1);
            it1 ++;
            it1 ++;
        }
        else
        {
            it1 = l.erase(it1);
        }
    }
    while(cur != fl.end())
    {
        if(*cur & 1)
        {
            cur = fl.insert_after(prev,*cur);
            cur++;
            prev = cur++;
        }
        else
        {
          cur =  fl.erase_after(prev);
        }
    }
    for(auto& e : fl)
        cout << e << " ";
    cout << endl;
    return 0;
}
