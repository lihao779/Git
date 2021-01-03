#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{

    multiset<string,greater<string>> m1;
    string fruit[] = {"apple","banana","orange","watermelon","apple","banana","apple"};
    for(auto& e:fruit)
    {
        cout<<e<<endl;
    }
    cout<<"----------------"<<endl;
    m1.insert(begin(fruit),end(fruit));
    for(auto& e:m1)
    {
        cout<<e<<endl;
    }
    cout<<m1.count("apple")<<endl;
    cout<<"----------------"<<endl;

    multimap<string,string> m;
    m.insert(make_pair("orange","橘子"));
    m.insert(make_pair("orange","橙子"));
    for(auto& e:m)
    {
        cout<<e.first<<"-"<<e.second<<endl;
    }

    m.erase("orange");
    cout<<"m_size:"<<m.size()<<endl;
    /*
    string fruit[] = {"apple","banana","orange","watermelon","apple","banana","apple"};
    set<string> s(begin(fruit),end(fruit));
    s.insert("grapes");
    for(auto& e:s)
    {
        cout<<e<<endl;
    }
    */
    return 0;
}



#if 0
class Compare
{
    public:
        bool operator()(const pair<string,size_t>& left,const pair<string,size_t>& right)
        {
            return left.second<right.second;
        }
};


int main()
{
    string fruit[] = {"apple","banana","orange","watermelon","apple","banana","apple"};
    map<string,size_t> m;
    for(auto& e:fruit)
    {
        m[e]++;
    }
    for(auto& e:m)
    {
        cout<<e.first<<"-"<<e.second<<endl;
    }
    priority_queue<pair<string,size_t>,vector<pair<string,size_t>>,Compare> q(m.begin(),m.end());
    /*
    vector<string> favorite;
    for(size_t i = 0;i<3;i++)
    {
        favorite.push_back(q.top().first);
        q.pop();
    }
    for(auto& e:favorite)
    {
        cout<<e<<endl;
    }
    sort(favorite.begin(),favorite.end());
    */
    set<string> s;
    for(int i = 0;i<3;i++)
    {
        s.insert(q.top().first);
        q.pop();
    }
    for(auto& e: s)
        cout<<e<<endl;
    return 0;
}
#endif
