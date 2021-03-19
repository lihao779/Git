#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    map<int, int> imap;
    imap.insert({1, 1});
    imap.insert({2, 2});
    imap.insert({3, 3});
    imap.insert({4, 4});
    imap.insert({5, 5});
    auto it = imap.lower_bound(3);
    cout << it->first << endl;
    it = imap.upper_bound(3);
    cout << it->first << endl;
    auto p = imap.equal_range(3);
    cout << p.first->first << " " << p.second->first << endl;
    return 0;
}
