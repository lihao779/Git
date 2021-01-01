#include<string.h>
#include<iostream>


using namespace std;

struct True
{
    static bool Get()
    {
        return true;
    }
};
struct False
{
    static bool Get()
    {
        return false;
    }
};

template<class T>
struct TypeTraites
{
    typedef False PODTYPE;
};
template<>
struct TypeTraites<int>
{
    typedef True PODTYPE;
};
    
    
template<class T>
void Copy(T* dst,const T* scr,size_t size)
{   
    if(TypeTraites<T>::PODTYPE::Get())
    memcpy(dst,scr,sizeof(T)*size);
    else
    {
        for(size_t i = 0;i<size;i++)
        {
            dst[i] = scr[i];
        }

    }
}

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
    ~String()
    {
        if(_str)
        {
            delete[] _str;
        }
    }
    String& operator=(const String& s)
    {
        if(&s!=this)
        {
            char* temp = new char[strlen(s._str)+1];
            strcpy(temp,s._str);
            delete[] _str;
            _str = temp;
        }
        return *this;
    }

    private:
        char* _str;
};

int main()
{
    /*
    int array1[] = {1,2,3,4,5};
    int array2[5];
    Copy(array2,array1,sizeof(array1)/sizeof(array1[0]));
    for(auto e:array2)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    */
    String s1[] = {"111","222","333"};
    String s2[3];
    Copy(s2,s1,3);

    return 0;

}
/*总结
 * memcpy是浅拷贝
 * 需要改用s1[1] = s2[1]这种形式
 * 因为当有资源管理时赋值运算符重载将会给出
 * 给出的都是以深拷贝给出的
 */
