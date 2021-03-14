#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int i = 2;
int main()
{
    string s[] = {"red","red","yello","pink","green","blue","blue"};
    vector<string> vec(begin(s),end(s));
    sort(vec.begin(),vec.end());
    auto uit = unique(vec.begin(),vec.end());
    vec.erase(uit,vec.end());
    stable_sort(vec.begin(),vec.end(),[](const string& s1,const string& s2)
                                        { return s1.size() < s2.size();});
    for(auto& e : vec )
    {
        cout << e << " ";
    }
    cout << endl;
    size_t count = 5;


    auto pit = partition(vec.begin(),vec.end(),[count](const string& s){return s.size() >= count;});

    cout << "have " << pit-vec.begin() << " ele_size big than " << count << endl;
    for(auto i = vec.begin();i != pit;i++)
    {
        cout << *i << " ";
    }
    cout << endl;
    for(auto& e : vec )
    {
        cout << e << " ";
    }
    cout << endl;

/*
    auto fit = find_if(vec.begin(),vec.end(),[count](const string& s){return s.size() >=count;});
    size_t num_count = vec.end() - fit;
    cout << "have " << num_count << " ele_size big than " << count << endl;
    for(;fit != vec.end();fit++)
    {
        cout << *fit << " ";
    }
    cout << endl;
    cout << "---------------------------" << endl;
    auto f = [](int left,int right)->int {return left + right;};
    cout << f(1,2) << endl;
    int i = 10;
    auto f1 = [&i](int num)->int {return num + i;};
    i = 1;
    cout << f1(3) << endl;
*/
    return 0;
}
