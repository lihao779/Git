#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <forward_list>
using namespace std;

int main()
{
    vector<int> vec1 = {1, 2, 3, 4, 5};
    vector<int> vec2;
    reverse_copy(vec1.begin(), vec1.end(), back_inserter(vec2));
    for(auto e: vec1)
        cout << e << " ";
    cout << endl;
    for(auto e: vec2)
        cout << e << " ";
    cout << endl;
    cout << "------------------" << endl;
    list<int> l1{1, 2, 3, 4, 5};
    list<int> l2{1, 3, 8, 9, 10};
    forward_list<int> l3 = {-1, 0};
    forward_list<int> l4 = {-3, 10};
    vector<int> vec3;
    merge(l1.begin(), l1.end(), l2.begin(), l2.end(), back_inserter(vec3));
    for(auto e: vec3)
        cout << e << " ";
    cout << endl;
    cout << l1.size() << " " << l2.size() << endl;
    l1.merge(l2);
    for(auto e: l1)
        cout << e << " ";
    cout << endl;
    cout << "------------------" << endl;
    auto bit = l3.before_begin(); 
    l3.splice_after(bit,l4);
    for(auto e: l3)
        cout << e << " ";
    cout << endl;
    return 0;
}
