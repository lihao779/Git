
#include <stdio.h>
#include <typeinfo>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
using namespace std;



void msg_err(initializer_list<string> l)
{
    auto begin = l.begin();
    for(;begin != l.end();begin++)
    {
        cout << *begin << " ";
    }
    cout << endl;
}

void Test1(int* left,int* right)
{
    int temp = *left;
    *left = *right;
    *right = temp;
}
void reset(int& i)
{
    i = 0;
}
bool isshorter(const string& s1,const string& s2)
{   
    return s1.size()<s2.size();
}

int find_char(const string& s,char c,int& occurs)
{
    occurs = 0;
    int ret = -1;
    for(size_t i = 0;i < s.size();i++)
    {
        if(s[i] == c)
        {
            occurs++;
            if(ret == -1)
                ret = i;
        }
    }
    return ret;
}

void Test2()
{
    int count = 0;
    string s;
    cin >> s;
    int index = find_char(s,'o',count);
    if(index != -1)
    {
        cout << s[index] << " count is "<< count<<endl;
    }
}

void swap(int& left,int& right)
{
    int temp = left;
    left = right;
    right = temp;
}


bool Issupper(const string& s)
{
    for(size_t i = 0;i<s.size();i++)
    {
        if(isupper(s[i]))
            return true;
    }
    return false;
}
void lowerstring(string& s)
{
    for(size_t i = 0;i<s.size();i++)
    {
        if(isupper(s[i]))
            s[i] += 32;
    }
}
void Test3()
{
    string s("helloWWeE");
    if(Issupper(s))
        cout<<"s has supper"<<endl;
    lowerstring(s);
    cout<<s<<endl;
}

void print(const int* cp)
{
    if(cp)
        while(*cp)
            cout<<*cp++<<" ";
}
void print(const int* begin,const int* end)
{
    while(begin != end)
        cout<<*begin++<<" ";
    cout<<endl;
}
void print(const int ia[],size_t size)
{
    for(size_t i = 0;i!=size;++i)
    {
        cout<<ia[i]<<" ";
    }
    cout<<endl;
}
void print(int (&arr)[3])
{
    cout<<typeid(arr).name()<<endl;
}

void print(int (*arr)[3],int row);

void swap(int** p1,int** p2)
{
    int* temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void Test4()
{
    string s1("hello"),s2("hello");
    if(s1 != s2)
        msg_err({"Nosame","hello","world"});
    else
        msg_err({"Same","okey"});
}

void err(const vector<string>& v)
{
    for(size_t i = 0;i<v.size();i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}
void Test5()
{
    err({"hello","hello"});
}
bool str_subrange(const string& s1,const string& s2)
{
    if(s1 == s2)
        return true;
    size_t size = (s1.size() <= s2.size() ? s1.size():s2.size());
    for(size_t i = 0;i != size;++i)
    {
        if(s1[i] != s2[i])
            return false;
    }
    return true;
}

int& get(int* arr,int index)
{
    return arr[index];
}
void gettest()
{
    int arr[10];
    for(int i = 0;i<10;++i)
        get(arr,i) = i;
    for(int i = 0;i<10;++i)
        cout<<arr[i]<<" ";
    cout<<endl;
}
void printv(vector<int>& v,int len)
{
    if(len == 1)
    {
        cout<<v[len-1]<<" ";
        return;
    }
    printv(v,len-1);
    cout<<v[len-1]<<" ";
}

/*
typedef int arrT[10];
using arrT = int[10];
typedef  string arrS[10];
using arrS = string[10];
string(&f1())[10];
auto f1(int)->string(&)[10];
arrS& f1(char);
int arr[3];
decltype(arr)& f1(double);
*/


void f1(const int*)
{
    cout<<"const int*"<<endl;
}
void f1(int*)
{
    cout<<"int*"<<endl;
}
void f1(int&)
{
    cout<<"int&"<<endl;
}
void f1(const int&)
{
    cout<<"const int&"<<endl;
}


const string& Shortstring(const string& s1,const string& s2)
{
    cout<<"const string&"<<endl;
    return s1.size() > s2.size() ? s2 : s1;
}
string& Shortstring(string& s1,string& s2)
{
    auto& r = Shortstring(const_cast<const string&>(s1),const_cast<const string&>(s2));
    cout<<"string&"<<endl;
    return const_cast<string&> (r);
}
int main()
{
    string s1,s2;
    Shortstring(s1,s2);
    return 0;
}

