#include <iostream>
#include <string>
using namespace std;

class Sales_date
{
    friend istream& read(istream& is,Sales_date& date);
    friend ostream& print(ostream& os,const Sales_date& date);
    friend Sales_date add(const Sales_date& th1,const Sales_date& th2);
    public:
    Sales_date() = default;
    Sales_date(const string &s)
        :ISBN(s)
    {}
    Sales_date(const string &s,unsigned n,double p)
        :ISBN(s)
         ,units_sold(n)
         ,revenue(p*n)
    {}
    Sales_date(istream& is)
    {
        double price = 0;
        is >> ISBN >> units_sold >> price;
        revenue = price * units_sold;
    }


    std::string isbn()const
    {
        return ISBN;
    }
    Sales_date& combine(const Sales_date&);
    double arg_price()const;

    private:
    std::string ISBN;
    unsigned units_sold;
    double revenue;
};
Sales_date& Sales_date::combine(const Sales_date& date)
{
    units_sold += date.units_sold;
    revenue += date.revenue;
    return *this;
}
double Sales_date::arg_price()const
{
    return revenue / units_sold;
}

///////////////////////////
//类外
istream& read(istream& is,Sales_date& date)
{
    double price;
    is >> date.ISBN >> date.units_sold >> price;
    date.revenue = date.units_sold*price;
    return is;
}
ostream& print(ostream& os,const Sales_date& date)
{
    os << date.isbn() <<" "<< date.units_sold << " "<< date.revenue <<" "
        <<date.arg_price();
    return os;
}
Sales_date add(const Sales_date& th1,const Sales_date& th2)
{
    Sales_date sum = th1;
    sum.combine(th2);
    return sum;
}

//构造
/*
Sales_date::Sales_date(istream& is)
{
    read(is,*this);
}
*/












class Person
{
    friend ostream& print(ostream& os,const Person& p);
    friend istream& read(istream& is,Person& p);
    public:
    Person() = default;
    Person(std::string name,std::string addr)
        :_name(name)
         ,_addr(addr)
    {}
    std::string Name()const
    {
        return _name;
    }
    std::string Addr()const
    {
        return _addr;
    }
    private:
    std::string _name;
    std::string _addr;
};
ostream& print(ostream& os,const Person& p)
{
    os << p._name << " - " << p._addr;
    return os;
}
istream& read(istream& is,Person& p)
{
    is >> p._name >> p._addr;
    return is;
}
////
/*
ostream& print(ostream& os,const Person& p)
{
    os << p.Name() << " " << p.Addr();
    return os;
}
istream& read(istream& is,Person& p)
{
    is >> p._name >>p._addr;
    return is;
}
*/
