#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Sale_date
{
    friend istream& read(istream& is,Sale_date& s);
    public:
        Sale_date() = default;
        Sale_date(string book,int count,double price)
            :book_(book)
             ,count_(count)
             ,totalprice_(price * count)
    {
    }
        Sale_date(string s)
            :Sale_date(s,0,0)
        {}
        Sale_date(istream& is)
            :Sale_date()
        {
            read(is,*this);
        }
    private:
        string book_;
        int count_;
        double totalprice_;
};
istream& read(istream& is,Sale_date& s)
{
    double price = 0;
    is >> s.book_ >> s.count_ >> price;
    s.totalprice_ = price * s.count_;
    return is;
}

class NoDefault
{
    public:
        NoDefault(int ra)
        {}
};
class C
{
    public:
        C(int c = int())
            :no(c)
        {}
    private:
        NoDefault no;
};












int main()
{
    Sale_date obj1();//obj1是一个函数
    Sale_date obj2 = cin;//obj2是一个对象
    Sale_date obj3 = string("ll");
    vector<C> vec;
    return 0;
}
