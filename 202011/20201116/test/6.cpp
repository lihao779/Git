#include<iostream>
#include<assert.h>
using namespace std;
template<class T,size_t N >
class array
{
    public:
        array()
            :size_(0)
        {}
        T& operator[](int index)
        {
            assert(index<size_);
            return array_[index];
        }
        const T& operator[](int index)const
        {
            assert(index<size_);
            return array_[index];
        }
        size_t size()const
        {
            return size_;
        }
    private:
        T array_[N];
        size_t size_;
};


#include<string.h>
//对模板进行特化
//1.先要有模板代码
//2.对于那种类型需要特化
//3。用该类型取特化该模板
/*
template<class T>
T Max(T left,T right)
{
    return left>right?left:right;
}
template<>
char* Max<char*>(char* left,char* right)
{
    if(strcmp(left,right)>0)
        return left;
    return right;
}

*/

template<class T>
const T& Max(const T& left,const T& right)
{
    return left>right?left:right;
}
const char*& Max(const char*& left,const char*& right)
{
    if(strcmp(left,right)>0)
        return left;

    return right;
}
int main()
{
     // array<int,10> a1;

    cout<<Max(10,20)<<endl;
    const char* p1 = "hello";
    const char* p2 = "World";
    cout<<Max(p1,p2)<<endl;
    return 0;
}
