#include <iostream>
#include <string>

using namespace std;

bool replace_string(string& s,const string& old_str,const string& new_str)
{
    //从s中查找，查找到后替换，替换完毕再从s+替换的位置后查找
    size_t pos = 0;
    while((pos = s.find(old_str,pos)) != string::npos)
    {
        s.replace(pos,old_str.size(),new_str);
        pos += new_str.size();
    }
    return true;
}

void Chancename(string& name,const string& begin_name,const string & end_name)
{
    name.insert(0,begin_name);
    name.insert(name.size() ,end_name);
}
int main()
{
    string s("AB21c4l5j7");
    string number("1234567890");
    int pos = 0;
    while((pos = s.find_first_of(number,pos)) != string::npos)
    {
        cout << s[pos] << " ";
        pos++;
    }

    while((pos = s.find_last_not_of(number,pos)) != string::npos)
    {
        cout << s[pos] << " ";
        string temp(s.begin(),s.begin()+ pos);
        s = temp;
    }
    return 0;
}
