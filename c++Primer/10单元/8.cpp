#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <deque>
#include <list>
#include <forward_list>
#include <iterator>
using namespace std;

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    list<int> l;
    copy(vec.begin(),vec.end(),front_inserter(l));
    for(auto& e: l)
        cout << e << " ";
    cout << endl;
    deque<int> d;
    copy(vec.begin(),vec.end(),back_inserter(d));
    for(auto& e: d)
        cout << e << " ";
    cout << endl;
    d.clear();
    copy(vec.begin(),vec.end(),inserter(d,d.begin()));
    for(auto& e: d)
        cout << e << " ";
    cout << endl;


    return 0;
}
