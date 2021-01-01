#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

void Test1()
{
    string s1;
    string s2;
    int k;
    cout<<"请输入字符串密钥S:";
    getline(cin,s1);
    cout<<"请输入间隔符K:";
    cin>>k;
    for(size_t i = 0;i<s1.size();i++)
    {
        if(islower(s1[i]))
            s1[i] = toupper(s1[i]);
    }
    char ch = '-';
    int count = 0;
    size_t index = 0;
    for(;index!=s1.size();index++)
    {
        if(s1[index]!=ch)
        {
            count++;
            s2+=s1[index];
            if(count>=k)
            {
                s2+=ch;
                break;
            }
        }
        else
        {
            if(count)
            {
                s2+=s1[index];
                break;
            }
        }
    }
    index++;
    count=0;
    for(;index!=s1.size();index++)
    {
        if(s1[index]!=ch)
        {
            count++;
            s2+=s1[index];
        }
        if(count==k)
        {
            count = 0;
            s2+=ch;
        }
    }
    if(s2[s2.size()-1]==ch)
    {
        s2.erase(s2.end()-1);
    }
    cout<<s2<<endl;
}



int main()
{
    Test1();
    return 0;
}
