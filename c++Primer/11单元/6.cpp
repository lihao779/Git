#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    map<string, vector<pair<string, string>>> imap; 
    string sub, name, bir;
    while(cin >> sub >> name >> bir)
    {
        imap[sub].push_back(make_pair(name, bir));
    }
    
    vector<string> vec1;
    multiset<string> iset;
    //copy(vec1.begin(), vec1.end(), inserter(iset, iset.end()));
    //copy(vec1.begin(), vec1.end(), back_inserter(iset));
    copy(iset.begin(), iset.end(), back_inserter(vec1));
    copy(iset.begin(), iset.end(), inserter(vec1,vec1.end()));
    map<string,int> imap1;
    imap1.insert({"hello", 1});
    imap1.insert(make_pair("helll", 2));
    imap1.insert(map<string, int>::value_type("hell", 3));
    imap1.insert(pair<string, int>("he", 4));
    for(auto& e: imap1)
        cout << e.first << "-" << e.second << " ";
    cout << endl;
    return 0;
}
