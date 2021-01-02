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
    cout<<m1["peach"]<<endl;
    cout<<m1["pear"]<<endl;
    return 0;
}
