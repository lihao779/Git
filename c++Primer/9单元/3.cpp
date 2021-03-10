#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

using namespace std;
int main()
{
    vector<int> v = {1,2,1,1,2,3};
    int some_val = 1;
    auto vb = v.begin();
    int size = v.size();
    int new_ele = 0;
    while(vb != (v.begin() + size/2 + new_ele))
    {
        if(*vb == some_val)
        {
            vb = v.insert(vb,some_val);
            vb++;
            vb++;
            new_ele++;
        }
        else
            vb++;
    }
    for(auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
    v.front() = 3;
    cout << v[0] << endl;
    return 0;

}
