#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <forward_list>
using namespace std;

int main()
{
    list<string> l = {"hello", "world", "hello", "world", "ye"};
    l.sort();
    l.unique();
    for(auto& e: l)
        cout << e << " ";
    cout << endl;
    return 0;
}
