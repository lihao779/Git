#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
    vector<int> vec;
    for(int i = 1;i <= 10;i++)
    {
        vec.push_back(i);
    }
    int sum = accumulate(vec.cbegin(),vec.cend(),0);
    cout << sum << endl;
    fill_n(vec.begin(),vec.size(),0);
    for(auto& e:vec)
    {
        cout << e << " ";
    }
    cout << endl;
    vector<int> vec2;
    copy(vec.cbegin(),vec.cend(),back_inserter(vec2));
    for(auto& e:vec2)
    {
        cout << e << " ";
    }
    cout << endl;
    return 0;
}
