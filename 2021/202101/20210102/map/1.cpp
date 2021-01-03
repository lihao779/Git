#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string,string> m1;
    m1.insert(pair<string,string>("orange","橘子"));
    m1.insert(pair<string,string>("apple","苹果"));
    m1.insert(pair<string,string>("banana","香蕉"));
    m1.insert(pair<string,string>("peach","梨子"));
    m1.insert(pair<string,string>("watermelon","西瓜"));

    map<string,string> m2 = {{"orange","橘子"},{"apple","苹果"},{"banana","香蕉"}};

    cout<<m1["peach"]<<endl;
    cout<<m1["pear"]<<endl;
    m1["pear"] = "梨";
    auto ret = m1.insert(make_pair("orange","橙子"));
    if(!ret.second)
    {
        cout<<m1[(*(ret.first)).first]<<endl;
        cout<<"插入失败"<<endl;
    }
    for(auto& e:m1)
    {
        cout<<e.first<<"-"<<e.second<<endl;
    }
    cout<<endl;
    
    std::map<std::string,std::string>::iterator it = m1.begin();
    while(it!=m1.end())
    {
        cout<<it->first<<"-"<<it->second<<endl;
        ++it;
    }
    cout<<endl;

    for(auto& e:m2)
    {
        cout<<e.first<<"-"<<e.second<<endl;
    }
    cout<<endl;
    auto it2 = m2.rbegin();
    while(it2!=m2.rend())
    {
        cout<<it2->first<<"-"<<it2->second<<endl;
        ++it2;
    }
    cout<<endl;
    cout<<"m1-size:"<<m1.size()<<endl;
    cout<<"m2-size:"<<m2.size()<<endl;
    cout<<"-----------------------------------------------"<<endl;
    m1.erase("orange");
    cout<<"m1-size:"<<m1.size()<<endl;
    auto pos = m1.find("orange");
    if(pos != m1.end())
    {
        m1.erase(pos);
    }
    cout<<"m1-size:"<<m1.size()<<endl;
    m1.erase(m1.begin(),m1.end());
    cout<<"m1-size:"<<m1.size()<<endl;
    return 0;
}
