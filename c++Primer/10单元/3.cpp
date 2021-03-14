
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;


bool Isshort(const string& s1,const string& s2)
{
    return s1.size() < s2.size();
}
bool Len_Is_4(string& s)
{
    return s.size() == 4;
}
int main()
{
    string s[] = {"red","red","yello","pink","green","blue","blue"};
    vector<string> vec(begin(s),end(s));

    sort(vec.begin(),vec.end());
    auto it = unique(vec.begin(),vec.end());
    vec.erase(it,vec.end());
    stable_sort(vec.begin(),vec.end(),Isshort);

    for(auto& e:vec)
    {
        cout << e << "  ";
    }
    cout << endl;
    //auto it_fi = find_if(vec.begin(),vec.end(),Len_Is_4);
    size_t i = 4;
    auto it_fi = find_if(vec.begin(),vec.end(),[i](const string& s){return s.size() >= i;});
    it_fi != vec.end() ? cout << *it_fi << endl : cout << "不存在" << endl;
    return 0;
}

