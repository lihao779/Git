#include<iostream>

using namespace std;

template<class T1,class T2>
class Date
{
    public:
        Date()
        {
            cout<<"Date(T1,T2)"<<endl;
        }
    private:
        T1 date1;
        T2 date2;
};
//全特化
template<>
class Date<int,int>
{
    public:
    Date()
    {
        cout<<"Date<int,int>"<<endl;
    }
    private:
        int date1;
        int date2;
};
//偏特化
template<class T>
class Date<T,int>
{
    public:
        Date()
        {
            cout<<"Date(T,int)"<<endl;
        }
    private:
        T date1;
        int date2;
};
template<class T1,class T2>
class Date<T1*,T2*>
{
    public:
        Date()
        {
            cout<<"Date<T1*,T2*>"<<endl;
        }
    private:
        T1* date1;
        T2* date2;
};

template<class T1,class T2>
class Date<T1&,T2&>
{
    public:
        Date(int& date1,int& date2)
            :date1_(date1)
             ,date2_(date2)
        {
            cout<<"Date<T1&,T2&>"<<endl;
        }
    private:
        T1& date1_;
        T2& date2_;
};

int main()
{
    Date<int*,int*> d1;
    int a1 = 10;
    int a2 = 20;
    Date<int&,int&> d2(a1,a2);
    Date<char,int> d3;
    Date<int,int> d4;
    Date<int,double> d5;
    return 0;
}
