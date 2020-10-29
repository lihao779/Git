#include<iostream>
#include<stdio.h>
#include<string.h>
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

        String(const String& s)
        :_str(new char[strlen(s._str)+1])
        {
            strcpy(_str,s._str);
        }
        
        String& operator=(const String& s)
        {
            //先释放空间，在申请空间，拷贝，赋值
            if(this!=&s)
            {
                /*
                delete[] _str;
                _str = new char[strlen(s._str)+1];
                strcpy(_str,s._str);
                */
                char* temp = new char[strlen(s._str)+1];
                strcpy(temp,s._str);
                delete[] _str;
                _str = temp;
            }
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
    private:
        char* _str;
};

int main()
{
    String s1("hello");
    String s2(s1);
    String s3("world");
    s3 = s1;
    return 0;
    
}
