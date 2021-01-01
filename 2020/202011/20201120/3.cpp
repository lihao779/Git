#include<string.h>
#include<iostream>
#include<cstdarg>
using namespace std;

void demo(const char* msg,...)
{
    va_list argp;//
    int argno = 0;
    char* para;
    va_start(argp,msg);
    while(1)
    {
        para = va_arg(argp,char*);
        if(strcmp(para,"\0")==0)
            break;
        cout<<para<<" ";
        argno++;
    }
    va_end(argp);
    cout<<endl;
}

int main()
{
    demo("hello","world","\0");
    return 0;
}
