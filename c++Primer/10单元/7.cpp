#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;

bool check_size(const string& str,size_t sz)
{
    return str.size() < sz;
}
int main()
{
    string s = "hello";
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    int num = 3;
    auto itf = find_if(vec.begin(),vec.end(),[num](int i)
                                    { return i >= num; });
    while(itf != vec.end())
    {
        cout << *itf << " ";
        itf++;
    }
    cout << endl;
    auto itf1 = find_if(vec.begin(),vec.end(),bind(check_size,s,_1));
    while(itf1 != vec.end())
    {
        cout << *itf1 << " ";
        itf1++;
    }
    cout << endl;

    return 0;
}
