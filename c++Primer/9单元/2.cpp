#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

using namespace std;

int main()
{
    string s;
    deque<string> d;
    int i = 2;
    while(i-- && cin >> s)
        d.push_back(s);
    auto db = d.begin();
    while(db != d.end())
    {
        cout << *db << " ";
        ++db;
    }
    cout << endl;

    list<string> l;
    int j = 2;
    while(j-- && cin >> s)
        l.push_back(s);
    auto lb = l.begin();
    while(lb != l.end())
    {
        cout << *lb << " ";
        ++lb;
    }
    cout << endl;

    return 0;
}
