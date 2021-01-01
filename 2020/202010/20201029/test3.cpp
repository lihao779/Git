#include<iostream>
#include<string.h>
#include<stdio.h>


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
        _count = new int(1);
    }

    String(const String& s)
        :_str(s._str)
         ,_count(s._count)
    {
        ++*_count;
    }

    ~String()
    {
        if(_str && 0 == --*_count)
        {
            delete[] _str;
            _str = NULL;
            delete _count;
        }
    }

    String& operator=(const String& s)
    {
        if(&s != this)
        {
            if(--*_count == 0)
            {
                delete[] _str;
                delete _count;
            }
            _str = s._str;
            _count = s._count;
            ++*_count;
            
        }
        return *this;
    }
    char& operator[](size_t index)
    {
        if(*_count > 1)
        {
            --*_count;
            char* temp = new char[strlen(_str)+1];
            strcpy(temp,_str);
            _count = new int(1);
            _str = temp;

        }
        return _str[index];
    }
    
    const char& operator[](size_t index)const
    {
        return _str[index];
    }

    void Get()const
    {
        cout<<_str<<" "<<*_count<<endl;
    }
private:
    char* _str;
    int* _count;
};

int main()
{
    String s1("hello");
    String s2(s1);
    String s3("2ello");
    s3 = s1;
    s1[0] = 'H';

    s1.Get();
    s2.Get();    
    s3.Get();


    string s4(20,'a');
    string s5(s4);
    printf("%p,%p\n",&s4[0],&s5[0]);
    printf("%p,%p\n",s4.c_str(),s5.c_str());
    return 0;
}
