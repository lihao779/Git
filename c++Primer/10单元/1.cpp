#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

int main()
{
    vector<int> vec;
    list<string> l;
    for(int i = 0;i < 10;i++)
    {
        vec.push_back(i);
        l.push_back("lihao");
    }
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    cout << count(vec.begin(),vec.end(),1) << endl;;
    cout << count(vec.begin(),vec.end(),2) << endl;;
    cout << count(vec.begin(),vec.end(),10) << endl;;
    cout << count(l.begin(),l.end(),"lihao") << endl;;
    return 0;
}
