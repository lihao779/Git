#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<iostream>
#include<stdlib.h>

using namespace std;


class String
{
public:
    String(const char* str = "")
    {
        if(str == NULL)
            str = "";
        _size = strlen(str);
        _capacity = strlen(str);
        _str = new char[strlen(str)+1];
        strcpy(_str,str);
    }

    String(const String& s)
        :_str(NULL)
    {
        _str = new char[s._size+1];
        strcpy(_str,s._str);
        _size = s._size;
        _capacity = s._capacity;
    }
    
    String& operator=(const String& s)
    {
        if(&s != this)
        {
            String temp(s);
            std::swap(_str,temp._str);
            _size = s._size;
            _capacity = s._capacity;
        }
        return *this;
    }

    size_t size()
    {
        return _size;
    }
    
    size_t capacity()
    {
        return _capacity;
    }

    size_t length()
    {
        return _size;
    }

    void resize(size_t n)
    {
        if(n>_capacity)
        {
            char* temp = new char[n+1];
            memset(temp,0,n+1);
            strcpy(temp,_str);
            delete[] _str;
            _str = temp;
            _capacity = n;
        }
        else if(n<_capacity)
        {
            _str[n] = '\0';
            _size = n;
        }
    }

    void clear()
    {
        _size = 0;
        _str[0] = '\0';
    }

    bool empty()
    {
        return _size == 0;
    }
    
    void reserve(size_t n)
    {
        if(n>_capacity)
        {
            char* temp = new char[n+1];
            memset(temp,0,n+1);
            strcpy(temp,_str);
            delete[] _str;
            _str = temp;
            _capacity = n;
        }
    }

    char& operator[](size_t index)
    {
        if(index<_size)
        {
            return _str[index];
        }
        else
        {
            cout<<"越界访问\n";
            exit(1);
        }
    }

    const char& operator[](size_t index)const
    {
        if(index<_size)
        {
            return _str[index];
        }
        else
        {
            cout<<"越界访问\n";
            exit(1);
        }
    }
    
    char& at (size_t index)
    {
        if(index<_size)
        {
            return _str[index];
        }
        else
        {
            cout<<"异常\n";
            exit(1);
        }
    }

    const char& at (size_t index)const
    {
        if(index<_size)
        {
            return _str[index];
        }
        else
        {
            cout<<"异常\n";
            exit(1);
        }
    }
    
    String& operator+=(char c)
    {
        if(_capacity<_size+1)
            reserve(2*_capacity);
        _str[_size++] = c;
        _str[_size] = '\0';
        return *this;
    }
    
    String& operator+=(const char* str)
    {
        size_t len = strlen(str);
        if(len+_size>_capacity)
            reserve(2*(len+_size));
        char buf[1024];
        memset(buf,0,sizeof(buf));
       size_t i = 0;
       size_t j = 0;
       for(i = 0,j = 0;i<(_size+len);i++)
       {
           if(i<_size)
           {
               buf[i] = _str[i];
           }
           else
           {
               buf[i] = str[j];
               j++;
           }
       }
       _size = len+_size;
       strcpy(_str,buf);
       return *this;
    }

    String& operator+=(const String& s)
    {
       *this+=s._str; 
       return *this;
    }
    

    friend ostream& operator<<(ostream& _out,const String& s)
    {
         _out<<s._str;
         return _out;
    }
    ~String()
    {
        if(_str)
        {
            delete[] _str;
            _str = NULL;
        }
    }
    void push_back(char c)
    {
        *this+=c;
    }
    String& append(const String& s)
    {
        *this+=s._str;
        return *this;
    }


    String& append(const char* str)
    {
        *this+=str;
        return *this;
    }


    String& assign(const char* str)
    {
        size_t len = strlen(str);
        if(len>_capacity)
        {
            reserve(2*len);
        }
        strcpy(_str,str);
        _size = len;
        return *this;
    }
    
    void swap( String& s)
    {
        char* chartemp = _str;
        _str = s._str;
        s._str = chartemp;

        int sizetemp,capacitytemp; 
        sizetemp = _size;
        capacitytemp = _capacity;
        _size = s._size;
        _capacity = s._capacity;
        s._size = sizetemp;
        s._capacity = capacitytemp;
    }
    

private:
    char* _str;
    size_t _size;
    size_t _capacity;
};


int main()
{



    String s1("hello");
    String s2("hhhhhhhh");
    cout<<s1<<endl;
    cout<<s1.size()<<endl;
    cout<<s1.capacity()<<endl;
    cout<<s2<<endl;
    cout<<s2.size()<<endl;
    cout<<s2.capacity()<<endl;
    s1.swap(s2);
    cout<<s1<<endl;
    cout<<s1.size()<<endl;
    cout<<s1.capacity()<<endl;
    cout<<s2<<endl;
    cout<<s2.size()<<endl;
    cout<<s2.capacity()<<endl;
    /*
    String s1("hello");
    String s2(s1);
    s2 = s1;
    cout<<s1.size()<<endl;
    cout<<s2.size()<<endl;
    cout<<s1.capacity()<<endl;
    cout<<s2.capacity()<<endl;
    s1.reserve(10);
    cout<<s1.capacity()<<endl;
    s1.clear();
    if(s1.empty())
    {
        printf("?\n");
    }
    cout<<s2<<endl;
    cout<<s2.size()<<endl;
    cout<<s2.capacity()<<endl;
    s2.reserve(20);
    cout<<s2.size()<<endl;
    
    s1 += 'c';
    cout<<s1<<endl;
    cout<<s1.size()<<endl;
    s2+='c';
    cout<<s2<<endl;
    cout<<s2.size()<<endl;
    s2+="world";
    String s1("hello");
    String s2("world");

    s1+=s2;
    s1.push_back('w');
    cout<<s1<<endl;
    cout<<s1.size()<<endl;
    cout<<s1.capacity()<<endl;

    */
    return 0;
}
