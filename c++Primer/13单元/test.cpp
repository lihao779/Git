#include <set>
#include <iostream>
using namespace std;


int main()
{
    set<int> s1;
    set<int> s2;
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(4);
    s1.insert(5);
    s2 = s1;
    for(auto e: s2)
        cout << e << " ";
    cout << endl;
    cout << s2.size() << endl;
    return 0;
}
