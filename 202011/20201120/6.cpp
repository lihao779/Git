#include<stdio.h>
#include<sstream>
#include<iostream>
using namespace std;
int main()
{
    int a = 123456;
    std::stringstream ss;
    ss<<a;
    string s;
    ss>>s;
    cout<<s<<endl;;
    cout<<ss.str()<<endl;
    ss.clear();
    ss.str("");
    double d = 12.34;
    ss<<d;
    ss>>s;
    cout<<s<<endl;;
    cout<<ss.str()<<endl;
    /*
    int a = 123456;
    char sz[32] = {0};
    sprintf(sz,"%d",a);
    printf("%s\n",sz);
    */
    /*
    stringstream ss;
    ss<<"hello";
    ss<<" ";
    ss<<"world";
    cout<<ss.str()<<endl;
    */
    return 0;
}
