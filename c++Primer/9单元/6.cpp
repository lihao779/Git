#include <iostream>
#include <string>
using namespace std;


void Func1(string& s,const string& old_val,const string& new_val)
{
    for(size_t i = 0;i < s.size();i++)
    {
        size_t j = 0;
        for(j = 0;j < old_val.size();j++)
        {
            if((i + j >= s.size()) || old_val[j] != s[i + j])
            {
                break;
            }
            
        }
        if(j == old_val.size())
        {
            //完全相等
            //删除[i,i+old_val.size())
            s.erase(i,old_val.size());
            s.insert(i,new_val);
            i = i + new_val.size() - 1;
        }

    }
}
void Func2(string& s,const string& old_val,const string& new_val)
{   
    auto sit = s.begin();
    for(; sit!= s.end();sit++)
    {
        auto oldit = old_val.begin();
        for(; oldit != old_val.end();oldit++)
        {
            if((sit + (oldit - old_val.begin()) == s.end()) || *(sit + (oldit - old_val.begin())) != *oldit)
            {
                break;
            }
        }
        if(oldit == old_val.end())
        {
            sit = s.erase(sit,sit+old_val.size());
            s.insert(sit,new_val.begin(),new_val.end());
            sit -= 1;
        }
    }
}

int main()
{
    string s1 = "Hello , world";
    string s2 = "Hello , world";
    string old_val = "Hello";
    string new_val = "world";

    Func1(s1,old_val,new_val);
    cout << s1 << endl;
    Func2(s2,old_val,new_val);
    cout << s2 << endl;
    return 0;
}
