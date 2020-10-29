#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

class String
{
    public:
        String(const char* str = "")
        {
            if(str == NULL)
                str = "";
           
            _str = new char[strlen(str)+1];
            strcpy(_str,str);
        }
    //简洁版（现代版）
        String(const String& s)
            :_str(NULL)
        {
            String temp(s._str);
            swap(_str,temp._str);
        }
        
        String& operator=( String s)
        {
            swap(s._str,_str);
            return *this;
        }


        ~String()
        {
            if(_str)
            {
                printf("_str:%p\n",_str);
                delete[] _str;
                _str = NULL;
            }
        }
        void Getstr()const
        {
            cout<<_str<<endl;
        }
    private:
        char* _str;
};

int main()
{
    String s1("hello");
    String s2(s1);
    String s3("world");
    s1 = s3;
    s1.Getstr();
    s2.Getstr();
    s3.Getstr();
    return 0;

    
}
